"""Functions that help us work with files and folders.
"""
import logging
import os
import argparse
from pathlib import Path, PureWindowsPath, PurePosixPath

from qmk.constants import MAX_KEYBOARD_SUBFOLDERS, QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.errors import NoSuchKeyboardError


def is_keyboard(keyboard_name):
    """Returns True if `keyboard_name` is a keyboard we can compile.
    """
    if not keyboard_name:
        return False

    # keyboard_name values of 'c:/something' or '/something' trigger append issues
    # due to "If the argument is an absolute path, the previous path is ignored"
    # however it should always be a folder located under qmk_firmware/keyboards
    if Path(keyboard_name).is_absolute():
        return False

    keyboard_json = QMK_FIRMWARE / 'keyboards' / keyboard_name / 'keyboard.json'

    return keyboard_json.exists()


def under_qmk_firmware(path=Path(os.environ['ORIG_CWD'])):
    """Returns a Path object representing the relative path under qmk_firmware, or None.
    """
    try:
        return path.relative_to(QMK_FIRMWARE)
    except ValueError:
        return None


def under_qmk_userspace(path=Path(os.environ['ORIG_CWD'])):
    """Returns a Path object representing the relative path under $QMK_USERSPACE, or None.
    """
    try:
        if HAS_QMK_USERSPACE:
            return path.relative_to(QMK_USERSPACE)
    except ValueError:
        pass
    return None


def is_under_qmk_firmware(path=Path(os.environ['ORIG_CWD'])):
    """Returns a boolean if the input path is a child under qmk_firmware.
    """
    if path is None:
        return False
    try:
        return Path(os.path.commonpath([Path(path), QMK_FIRMWARE])) == QMK_FIRMWARE
    except ValueError:
        return False


def is_under_qmk_userspace(path=Path(os.environ['ORIG_CWD'])):
    """Returns a boolean if the input path is a child under $QMK_USERSPACE.
    """
    if path is None:
        return False
    try:
        if HAS_QMK_USERSPACE:
            return Path(os.path.commonpath([Path(path), QMK_USERSPACE])) == QMK_USERSPACE
    except ValueError:
        return False


def keyboard(keyboard_name):
    """Returns the path to a keyboard's directory relative to the qmk root.
    """
    return Path('keyboards') / keyboard_name


def keymaps(keyboard_name):
    """Returns all of the `keymaps/` directories for a given keyboard.

    Args:

        keyboard_name
            The name of the keyboard. Example: clueboard/66/rev3
    """
    keyboard_folder = keyboard(keyboard_name)
    found_dirs = []

    if HAS_QMK_USERSPACE:
        this_keyboard_folder = Path(QMK_USERSPACE) / keyboard_folder
        for _ in range(MAX_KEYBOARD_SUBFOLDERS):
            if (this_keyboard_folder / 'keymaps').exists():
                found_dirs.append((this_keyboard_folder / 'keymaps').resolve())

            this_keyboard_folder = this_keyboard_folder.parent
            if this_keyboard_folder.resolve() == QMK_USERSPACE.resolve():
                break

        # We don't have any relevant keymap directories in userspace, so we'll use the fully-qualified path instead.
        if len(found_dirs) == 0:
            found_dirs.append((QMK_USERSPACE / keyboard_folder / 'keymaps').resolve())

    this_keyboard_folder = QMK_FIRMWARE / keyboard_folder
    for _ in range(MAX_KEYBOARD_SUBFOLDERS):
        if (this_keyboard_folder / 'keymaps').exists():
            found_dirs.append((this_keyboard_folder / 'keymaps').resolve())

        this_keyboard_folder = this_keyboard_folder.parent
        if this_keyboard_folder.resolve() == QMK_FIRMWARE.resolve():
            break

    if len(found_dirs) > 0:
        return found_dirs

    logging.error('Could not find the keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard_name)


def keymap(keyboard_name, keymap_name):
    """Locate the directory of a given keymap.

    Args:

        keyboard_name
            The name of the keyboard. Example: clueboard/66/rev3
        keymap_name
            The name of the keymap. Example: default
    """
    for keymap_dir in keymaps(keyboard_name):
        if (keymap_dir / keymap_name).exists():
            return (keymap_dir / keymap_name).resolve()


def normpath(path):
    """Returns a `pathlib.Path()` object for a given path.

    This will use the path to a file as seen from the directory the script was called from. You should use this to normalize filenames supplied from the command line.
    """
    path = Path(path)

    if path.is_absolute():
        return path

    return Path(os.environ['ORIG_CWD']) / path


def unix_style_path(path):
    """Converts a Windows-style path with drive letter to a Unix path.

    Path().as_posix() normally returns the path with drive letter and forward slashes, so is inappropriate for `Makefile` paths.

    Passes through unadulterated if the path is not a Windows-style path.

    Args:

        path
            The path to convert.

    Returns:
        The input path converted to Unix format.
    """
    if isinstance(path, PureWindowsPath):
        p = list(path.parts)
        p[0] = f'/{p[0][0].lower()}'  # convert from `X:/` to `/x`
        path = PurePosixPath(*p)
    return path


class FileType(argparse.FileType):
    def __init__(self, *args, **kwargs):
        # Use UTF8 by default for stdin
        if 'encoding' not in kwargs:
            kwargs['encoding'] = 'UTF-8'
        return super().__init__(*args, **kwargs)

    def __call__(self, string):
        """normalize and check exists
            otherwise magic strings like '-' for stdin resolve to bad paths
        """
        norm = normpath(string)
        return norm if norm.exists() else super().__call__(string)
