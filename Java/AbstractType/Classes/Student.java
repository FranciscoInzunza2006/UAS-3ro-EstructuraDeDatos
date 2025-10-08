package AbstractType.Classes;

public class Student {
    String name;
    int age;

    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public void sayHello() {
        System.out.printf("Hello, my name is %s.\nI'm %d years old.", name, age);
    }
}
