# C++ doesn't have a nice standard JSON serializer :(

# Written for the Python interpeter at "http://ideone.com/"

import json
import sys

def sum_numbers(obj):
  if type(obj) == type(dict()): # Objects
    if "red" in obj.values():
      return 0
    return sum(map(sum_numbers, obj.values()))
  if type(obj) == type(list()): # Arrays
    return sum(map(sum_numbers, obj))
  if type(obj) == type(0): # Strings/Numbers
    return obj
  return 0


def main():
  input = sys.stdin.read()
  data = json.loads(input)

  print sum_numbers(data)
  return 0

main()