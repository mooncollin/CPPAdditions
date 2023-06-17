import os
import pathlib
import argparse
import shutil
from typing import (
    Set
)

from jinja2 import Environment, FileSystemLoader

env = Environment(
    loader=FileSystemLoader(f'{os.path.dirname(__file__)}')
)

TEMPLATES_FOLDER    = pathlib.Path('templates')
DOCS_FOLDER         = pathlib.Path('docs')

def replacement_location(path: pathlib.Path, find: pathlib.Path, replace: pathlib.Path) -> pathlib.Path:
    index = path.parts.index(str(find))

    if index < 0:
        raise ValueError(f'Unable to find a replacement location for {path}')

    return pathlib.Path().joinpath(*path.parts[0:index]).joinpath(replace).joinpath(*path.parts[index + 1:])

def generate_templates(directory: pathlib.Path, ignore_files: Set = set()):
    for item in directory.iterdir():
        if item not in ignore_files:
            full_path = replacement_location(item, TEMPLATES_FOLDER, DOCS_FOLDER)
            print(f'Generating {full_path}')
            if item.is_dir():
                full_path.mkdir(exist_ok=True)
                generate_templates(item, ignore_files)
            else:
                template = env.get_template(item.as_posix())
                with full_path.open('w') as f:
                    template.stream().dump(f)

if __name__ == '__main__':
    parser = argparse.ArgumentParser('Generates documentation for the C++ libraries')
    parser.add_argument('--delete', action='store_true', default=False, help='Deletes the docs before generating')

    args = parser.parse_args()

    delete: bool = args.delete

    if delete:
        for path in DOCS_FOLDER.iterdir():
            if path.is_file():
                path.unlink()
            elif path.name != 'src':
                shutil.rmtree(path)

    generate_templates(TEMPLATES_FOLDER, {
        TEMPLATES_FOLDER / 'base.html',
        TEMPLATES_FOLDER / 'macros.html',
        TEMPLATES_FOLDER / 'library.html',
        TEMPLATES_FOLDER / 'item_page.html',
        TEMPLATES_FOLDER / 'end_page.html'
    })