#!/usr/bin/env python

import optparse

parser = optparse.OptionParser()
parser.add_option('-t', '--test', help='gives you 42', action='store_const', const=42)
parser.add_option('-s', '--stuff', help='tests', type='int')
(options, args) = parser.parse_args()

if options.test:
    print(options.test)

if options.stuff:
    print('stuff: {}'.format(options.stuff))

print('positional arguments: {}'.format(','.join(args)))
