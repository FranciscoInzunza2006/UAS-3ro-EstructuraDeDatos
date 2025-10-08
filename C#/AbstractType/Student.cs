
namespace CShard
{
    public class Student
    {
        string name;
        int age;

        public Student(string name, int age)
        {
            this.name = name;
            this.age = age;
        }

        public void sayHello()
        {
            Console.WriteLine($"Hello, my name is {name}.\nI'm {age} years old.");
        }
    }
}