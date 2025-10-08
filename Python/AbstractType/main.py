
class Student:
    def __init__(self, name:str, age:int):
        self.name = name
        self.age = age

    def sayHello(self):
        print("Hello, my name is {}.\nI'm {} years old.".format(self.name, self.age))

def main():
    student = Student("Francisco", 19)
    student.sayHello()

if __name__ == "__main__":
    main()