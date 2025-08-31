"use strict"

class Student {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    sayHello() {
        console.log(`Hello, my name is ${this.name}.\nI'm ${this.age} years old.`);
    }
}

let student = new Student("Francisco", 19);
student.sayHello();