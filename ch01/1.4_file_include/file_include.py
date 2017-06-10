#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import os
import sys


class IncludeParser(object):

    def __init__(self, input_file: str):
        self._input_file = input_file
        self._output_buffer = ''

    def parse(self, output_file: str):
        with open(output_file, 'w') as fp:
            self._parse_include_syntax(self._input_file)
            fp.write(self._output_buffer)

    def _parse_include_syntax(self, input_file):
        if not os.path.exists(input_file):
            raise RuntimeError('input file({}) not found'.format(input_file))
        with open(input_file, 'r') as fp:
            for line in fp:
                if line.startswith('include'):
                    try:
                        include_file = line.split(' ')[1]
                        self._parse_include_syntax(include_file.strip())
                    except IndexError:
                        raise RuntimeError('include syntax error')
                else:
                    self._output_buffer += line


if __name__ == '__main__':
    if (len(sys.argv) < 3):
        raise RuntimeError('Usage: {} [output.file] [input.file]')
    parser = IncludeParser(sys.argv[-1])
    parser.parse(sys.argv[-2])
