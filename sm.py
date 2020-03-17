class Stack:
  def __init__(self):
    self.data = [0]

  def push(self, x: int):
    self.data.append(x)

  def pop(self) -> int:
    return self.data.pop()

  def peak(self) -> int:
    return self.data[-1]


class Register:
  def __init__(self):
    self.data = 0

  def set(self, x: int):
    self.data = x

  def get(self) -> int:
    return self.data


class Memory:
  def __init__(self):
    self.data = []

  def set(self, k: int, x: int):
    self.data[k] = x

  def get(self, k: int) -> int:
    return self[k]


class Proc:
  def __init__(self):
    self.cs = Stack()  # call stack
    self.ds = Stack()  # data stack

    self.stt = Register()  # status reg.
    self.memory = Memory()

  def run(self):
    while self.stt^1:  # halt flag off
      [push, add, out, halt][self.memory.get(self.cs.peak())]()
      self.cs.push(self.cs.peak()+1)
