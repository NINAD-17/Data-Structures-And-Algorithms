# Object Oriented Programming

## Object
It's a programming technique in which things work around object.
Object is an entity, which has two things, 
    1. State or property
    2. Behaviour

We use real world objects to bring our program close to the real world. It increases readability of our program, manageability and extensibility.

## What is class?
Ex - `Hero Ninad;` here we made `Ninad` variable/object by using data type `Hero`

In object-oriented programming (OOP), a class is a blueprint or template for creating objects. It defines the properties (data members) and behaviors (member functions) that the objects of that class will have. **Think of a class as a user-defined data type**.

An object is an instance of a class. When you create an object, you’re essentially creating a variable of that class type. Objects allow you to work with the data and methods defined within the class. In your example, `Ninad` would be an object of the Hero class.

A variable is a named storage location in memory that holds a value. In the context of OOP, when you create an object, you’re also creating a variable of that class type. So, **`Ninad` is both an object and a variable**.

### Size of Object
If you check the size of object then it will be total of all the properties. 
When object is created from an empty class (no properties are defined), then it's size will be 1. Because by default system gives 1 byte to the object.

### Padding and Alignment
 The actual size of the class may not always match the sum of the sizes of its individual data members due to padding and alignment considerations.

- Theoretical Size
    - `int health` (4 bytes on most systems)
    - `char level` (1 byte)
    
    - The theoretical size of the class would be `4 + 1 = 5` bytes.

- Greedy Alignment
    - Greedy alignment refers to a technique used by the compiler to minimize padding.
    - The compiler orders the data members in decreasing order of size (largest to smallest).
    - In the `Hero` class:
        - `int health` (4 bytes) is larger than `char level` (1 byte).
    So, the compiler places health first, followed by level.
        - The total size becomes 4 (health) + 4 (padding) + 1 (level) = 9 bytes.
    - However, due to greedy alignment, the compiler rounds up the size to the nearest multiple of the largest alignment requirement (which is 4 bytes in this case).
    Hence, the final size of the Hero class is 8 bytes.

- Static Members and Member Functions
    - Static data members and member functions do not contribute to the size of the class or objects.
    - They have only one instance shared among all objects, and member functions are executable code without a size like data members.

- Size of Derived Class
    - When you create a derived class, it inherits the data members from the base class.
    - The size of the derived class includes both the base class data members and any additional data members introduced in the derived class.

Therefore, **size of a class depends on the data members, their alignment requirements, and the compiler’s padding strategy**.

- Summarized explaination of padding and alignment
As the theretical size is 5, it's not aligned with most largest object member's data type size. It's necessary to do that for optimization purposes. So it uses 3 out of 4 bytes (from alignment of int) and makes size equal to 8 bytes. 
**It's not memory waste**.

    <img src="padding_alignment.jpg" >


- **More Explaination of Padding concept:**
    - **Why alignment exists**
        - Modern CPUs usually access memory in words (4 bytes on 32‑bit, 8 bytes on 64‑bit).
        - But alignment is based on the largest member type in the class, not always fixed at 4 or 8.
            Example:
            - If your class has a double (8 bytes), the object size will be rounded up to a multiple of 8.
            - If the largest member is int (4 bytes), the object size will be rounded up to a multiple of 4.
        - If data isn’t aligned, the CPU may need extra work (slower access).
        - When you explicitly declare an array of objects, they are stored consecutively in memory `Hero heroes[10];`. Otherwise, individual objects are separate and not in an array
        - Padding matters because in such arrays, each object must start at a properly aligned address.
        - That’s why the compiler ensures the size of each object is a multiple of the largest alignment requirement.
    - **What is padding really?**
        - Padding = unused bytes inserted by the compiler.
        - They are not “garbage data you can use.” They are just reserved to ensure the next member or next object in an array starts at the correct aligned address.
        - You cannot rely on their contents — they are simply ignored space.
        Example:
        `double a; double b; short s;`
        - double = 8 bytes, must start at multiple of 8.
        - short = 2 bytes.
        `[a: 8][b: 8][s: 2][padding: 6]`
        - Total theoretical = 18, padded to 24 (next multiple of 8).
        - So object size = 24.

### External Class
You can able to define class in external file. To do this make a cpp file and write the class in it. In original file where you want to add that class, simply include that file path in `"..."` this.

## Accessing data members
You can able to access data members by using `.` (dot) operator.
Ex - see in file `1_intro.cpp`

## Access Modifiers
It defines accessibility of data members and methods of the class. It tells where its scope lies.
There're 3 access modifiers:
- **Public**: You can access data members anywhere (inside and outside of the class)
- **Private** (by default): Only accessible in class (not outside)
- **Protected**

### Getters and setters
To access private data members outside of the class we use getters and setters. These are functions defined in the class by which we can access private data members.

## Behind the scenes of Object Initialization
### Constructors
1. **Default Constructor**
    - It first invokes a constructor.
    - Default constructor initializes the members of the class to their default values.
    - When `Hero ironman;` executes then it calls the `ironman.Hero()`. It's created by default. It's called **default constructor**.
    - You can also able to write it explicitly.
    - Since you haven’t defined a constructor for the Hero class, the compiler generates a default constructor for you.
    - The default constructor initializes each member variable to its default value:
        - int health will be initialized to 0.
        - char level will be initialized to the null character ('\0').
    - So, after creating an instance of Hero (like Hero h;), the health will be 0, and the level will be '\0'.


    ```
    class Hero {
        public:
            int health;
            char level;
            Hero(int h) : health(h) {}
    };
    ```

    in this case h.level will be uninitialized. (its value is indeterminate).

2. **Parameterized Constructor**
    ```
        Hero(int health) {
            health = health;
        }
    ```
    In above code, health (temp health/parameter variable) is giving it's value again to it (concept -> variable scoping - health is parameter variable and not actual variable defined in constructor)

- **`this` keyword**
    
    It stores the address of current object. It's a pointer that's why you can access it by `(*this).__` or `this -> __`
        
    - by using `this -> health = health`, it solves that confusion and assigns the ironman's health value equals to health value get from parameter.

- When you make any constructor explicitly then default constructor will not work, it's gone. So after creating parameterized constructor, you're trying to access default constructor it will not work.

3. **Copy constructor**: 
    - A copy constructor is a special constructor that creates a new object as a copy of an existing object.
    - Whenever you write a class then automatically it also makes a copy constructor.
    - So that you can able to use `Hero hulk(spiderman)`. It will copy all the object member's values into hulk.
    - Infinite loop in copy constructor: If you define your own copy constructor as
    ```
    Hero(Hero temp) {
    
    }
    
    Hero hulk(spiderman);
    ```

    - In this case `spiderman` is passed by value to the `temp`. Therefore temp is making copy of `spiderman` object and to make copy it calls (temp calls) the copy constructor, and it gets stuck in infinite loop.

    - When you create `Hero hulk(spiderman);`, the following happens:
    `spiderman` is passed by value to the copy constructor (i.e., temp is a copy of spiderman).
    - Inside the copy constructor, the compiler attempts to create a copy of temp (which is itself a copy of spiderman).
    This process repeats indefinitely, leading to an infinite loop.
- Fixing the Issue:
To avoid the infinite loop, you should pass the object by reference (const reference, ideally) instead of by value:
    ```
    Hero(const Hero& temp) {
        // Implementation
    }
    ```

- By passing by reference, you avoid making unnecessary copies and prevent the infinite recursion.

Passing by reference (const reference) allows you to work with the original object directly without creating additional copies.

- Infinite loop stack for copy constructor:
1.  **Initial Call:**
    -   `Hero hulk(spiderman)`:
        -   `spiderman` is passed by value to the copy constructor.
        -   Inside the copy constructor, a new object (let's call it `temp1`) is created as a copy of `spiderman`.
2.  **First Iteration:**
    -   `temp1(spiderman)`:
        -   Now, `temp1` (a copy of `spiderman`) is passed to the copy constructor.
        -   Another new object (let's call it `temp2`) is created as a copy of `temp1`.
3.  **Second Iteration:**
    -   `temp2(temp1)`:
        -   The process continues:
            -   `temp2` (a copy of `temp1`) is passed to the copy constructor.
            -   A new object (let's call it `temp3`) is created as a copy of `temp2`.
4.  **Third Iteration:**
    -   `temp3(temp2)`:
        -   And again:
            -   `temp3` (a copy of `temp2`) is passed to the copy constructor.
            -   A new object (let's call it `temp4`) is created as a copy of `temp3`.
5.  ... Infinite ...

- Simple explaination:
    `Hero(Hero otherHero) { ... }`
    - Here, otherHero is passed by value.
    - To pass by value, the compiler must create a copy of the argument (spiderman) to initialize otherHero.
    - But how do we create that copy? → By calling the copy constructor.
    - But we are inside the copy constructor definition itself!
    - So calling it requires another copy constructor call → infinite recursion.
    👉 That’s why it loops forever:
    - `Hero hulk(spiderman)` calls copy constructor.
    - To pass spiderman by value, it tries to copy spiderman into otherHero.
    - That copy again calls the copy constructor, which again tries to copy by value… and so on infinitely.

- After writing own copy constructor, default copy constructor gets dead.


- **Deep copy and Shallow copy:**
- Shallow copy: It's done by default. In this it uses same memory location for each object's object member.
- Deep copy: In this instead of using same memory location it uses different. 
- See the example in `5_Shallow_and_Deep_copy.cpp`.

Copy assignment operator
In this you can copy the object member's of one object to another.


## Destructor
It's used to deallocate the memory.
As soon as your objects are about to out of scope (lifetime is about to end) then destructor is called to free the memory.
When you create a class, it automatically creates destructor.
Like constructor, destructor don't have any return type. It doesn't contain any input parameters.
Destructor is differentiated by using `~` sign.
For the static allocation destructor is automatically being called.
But for dynamically we need to call destructor manually by using keyword `delete`.


## Constant keyword
1.  `const` Keyword:

    -   The `const` keyword is used to declare constants or unchangeable values.
    -   It indicates that an object (variable, pointer, member function, etc.) cannot be modified after its initial assignment.
    -   `const` can be applied to variables, pointers, member functions, objects, and references.

        Some cases with constant keyword
        - `const int` → value itself is constant.
        - `const int*` → pointer to constant value (cannot change value, can change pointer).
        - `int* const` → constant pointer to int (cannot change pointer, can change value).
        - `const int* const` → constant pointer to constant int (cannot change either).
2.  Constant Variables:

    -   When you declare a variable as `const`, it cannot be modified after initialization.
    -   Rules for declaring and initializing constant variables:
        -   The `const` variable must be initialized at the time of declaration.
        -   It cannot be assigned a value anywhere else in the program.
        -   An explicit value must be provided during declaration.

3. const with Pointer Variables: see example in `7_Const_and_Static_Keyword.cpp`
    - You can declare member functions as const to indicate that they do not modify the object’s state.
    - A const member function cannot modify non-static data members.

4. Creating const Member Functions: see example in `7_Const_and_Static_Keyword.cpp`
    - Initialization lists are used in constructors to initialize class members.
    - They allow direct initialization of data members.
    - A const member function can be called on any type of object (both const and non-const objects).
    - When an object is declared as const, it must be initialized at the time of declaration (usually using constructors).
    - The idea of const functions is to prevent accidental changes to objects.

5. Constant Objects:
    - In C++, a constant object (also known as a const object) is an object that cannot be modified after its initial creation. When you create a constant object, you guarantee that its state remains unchanged throughout its lifetime

    - Important Notes:
        - A constant object must be initialized at the time of declaration.
        - Once a const object is initialized, any attempt to modify its data members is disallowed.
        - You cannot assign a new value to the data members of a const object.
        - Const objects are useful when you want to ensure that an object’s state remains unchanged.
    - Benefits of Const Objects:
        - Prevent accidental modifications: Const objects help prevent unintended changes to object state.
        - Useful for read-only access: Const objects are suitable for scenarios where you only need to read data from an object.

## static Keyword

It creates a data member which belongs to class. It means to access it we don't need to create object.

## Static functions
Don't need to create object. It doesn't have this keyword. Because this keyword is pointer to current object but there's no object.
Static functions can only access static members.


# OOPs Part 2
## Encapsulation
Encapsulation = wrapping **data members (state)** and **member functions (behavior)** together inside a class. 

So yes, every class in C++ is an example of encapsulation because it groups members and functions together. But encapsulation is not just about grouping — it’s also about controlling access to those members.

In C++, you can mark members as:
- **public** → accessible from outside the class.
- **private** → accessible only inside the class.
- **protected** → accessible inside the class and derived classes.

👉 Encapsulation is strongest when you use private/protected members and expose controlled access via public methods (getters/setters). That’s why people often equate “encapsulation” with “private members.”

But technically:

Even if you make everything public, the class is still encapsulating data + behavior.
It’s just **weak encapsulation** because you’re not hiding anything.

**Visualize it as medicine inside a capsule**:
It’s like putting medicine inside a capsule — everything related is bundled together.
- The capsule itself = class.
- The medicine inside = private data.
- The outer shell = public methods (controlled access).

If you break the capsule and expose everything, it’s still a capsule, but it’s not serving its purpose.

Encapsulation ensures data hiding and controlled access.

**Key Points:**
- **Data hiding**: By making members private, you prevent direct access from outside the class.

- **Controlled access**: You expose only what’s necessary using public methods (getters/setters).

- **Fully encapsulated class**: All data members are private.

- **Benefits**:
    - Security → sensitive data cannot be modified directly.
    - Flexibility → you can change internal implementation without affecting outside code.
    - Read‑only objects → possible by providing only getters.
    - Code reusability → same class can be reused in different programs.
    - Unit testing → easier to test small, encapsulated units.

Think of a capsule:
```
+---------------------------+
|   Student Class Capsule   |
|                           |
|  [Private Data]           |
|   - name                  |
|   - age                   |
|   - height                |
|                           |
|  [Public Functions]       |
|   - getAge()              |
|   - setAge()              |
|   - getName()             |
|   - setName()             |
|   - printDetails()        |
+---------------------------+
```
- Outside world cannot directly touch the private data.
- They must go through the public functions (like a capsule’s outer shell).
- This ensures safety and control.


## Inheritance
- **Inheritance** is an OOP concept where one class (child/derived class) can reuse the properties and behaviors of another class (parent/base class).
- It helps in **code reusability**, **extensibility**, and establishing an **“is‑a” relationship** between classes.
- Example:  
  - `Human` class has properties like `height`, `weight`, `age`.  
  - `Male` and `Female` classes can inherit these properties instead of rewriting them.

  ---

### Terminology
- **Base Class / Parent Class / Super Class** → The class whose members are inherited.  
- **Derived Class / Child Class / Sub Class** → The class that inherits from the base class.  

    Example:
    ```cpp
    class Human {   // Base class
        int age;
        int height;
    };

    class Male : public Human {   // Derived class
        string beardStyle;
    };
    ```

### Modes of Inheritance
Inheritance mode decides how the access modifiers of base class members behave in the derived class.
![Modes of Inheritance](modes_of_inheritance.png)
👉 Key point: Private members of base class are never directly inherited. But they can still be accessed indirectly via base class’s public/protected methods.

---

To understand modes of inheritance without confusion, think of the inheritance mode as a **ceiling filter**:

> **The Ceiling Rule:** The inheritance mode sets the *maximum visibility* that inherited base members can have in the derived class. It can downgrade access, but it can never upgrade it.

Also remember the golden rule: **Base class `private` members are never directly accessible to any derived class**, regardless of the inheritance mode used.

### The Three Perspectives to Keep in Mind

For any member inherited from `Parent`, always check 3 things:

1. **Inside `Child`:** Can methods inside `Child` touch it?
2. **Outside (via Object):** Can `childObj.member` be called in `main()`?
3. **Inside `GrandChild`:** If another class inherits from `Child`, can it access that member?

### 1. The Base Class Setup

```cpp
class Parent {
public:
    int pub = 1;
protected:
    int prot = 2;
private:
    int priv = 3;
};

```

### 2. Public Inheritance (`class Child : public Parent`)

This represents an **"IS-A"** relationship (e.g., a `Dog` is an `Animal`). Members retain their original access levels.

* `pub` remains **`public`**

* `prot` remains **`protected`**

* `priv` is **not accessible**


```cpp
class Child : public Parent {
    void test() {
        pub = 10;   // OK: public stays public
        prot = 20;  // OK: protected stays protected
        // priv = 30; // ERROR: private is never directly accessible
    }
};

class GrandChild : public Child {
    void test() {
        pub = 100;  // OK: still public
        prot = 200; // OK: still protected
    }
};

int main() {
    Child c;
    c.pub = 5;      // OK: pub is public
    // c.prot = 6;  // ERROR: prot is protected (hidden from outside)
}

```

### 3. Protected Inheritance (`class Child : protected Parent`)

The ceiling is set to **`protected`**. Public members are demoted to protected.

* `pub` becomes **`protected`**

* `prot` remains **`protected`**

* `priv` is **not accessible**


```cpp
class Child : protected Parent {
    void test() {
        pub = 10;   // OK: accessible inside Child
        prot = 20;  // OK: accessible inside Child
    }
};

class GrandChild : public Child {
    void test() {
        pub = 100;  // OK: inherited as protected, so GrandChild can still access it
        prot = 200; // OK: protected in Child, so GrandChild can still access it
    }
};

int main() {
    Child c;
    // c.pub = 5;  // ERROR: pub was demoted to protected!
    // c.prot = 6; // ERROR: protected
}

```

### 4. Private Inheritance (`class Child : private Parent`)

The ceiling is set to **`private`**. Everything inherited is demoted to private inside `Child`. This models an **"implemented-in-terms-of"** relationship.

* `pub` becomes **`private`**

* `prot` becomes **`private`**

* `priv` is **not accessible**


```cpp
class Child : private Parent {
    void test() {
        pub = 10;   // OK: accessible inside Child
        prot = 20;  // OK: accessible inside Child
    }
};

class GrandChild : public Child {
    void test() {
        // pub = 100;  // ERROR: pub became private in Child!
        // prot = 200; // ERROR: prot became private in Child!
    }
};

int main() {
    Child c;
    // c.pub = 5;  // ERROR: pub is private in Child
}

```

### Questions

* **"If inheritance is public, can child access everything?"** - Almost: it can access `public` and `protected`, but **never** `private`.


* **"Can further derived classes also access it in public inheritance?"** - Yes, `GrandChild` can access `public` and `protected` members of `Parent`.


* **"When it's private, can Child access Parent, but GrandChild cannot?"** - Exactly right. `Child` can access `Parent`'s `public` and `protected` members, but inside `Child` they turn into `private`. Therefore, `GrandChild` is locked out completely.


In modern Low-Level Design (LLD), **public inheritance** is used >95% of the time because it adheres to the **Liskov Substitution Principle (LSP)**. Private inheritance is rarely used—composition (has-a) is almost always preferred over private inheritance.

---

### Types of Inheritance
1. **Single Inheritance** → One base class, one derived class.
```cpp
class A { ... };
class B : public A { ... };
```

2. **Multilevel Inheritance** → A class inherits from another derived class.
```cpp
class A { ... };
class B : public A { ... };
class C : public B { ... };
```

3. **Multiple Inheritance** → A class inherits from more than one base class.
```cpp
class A { ... };
class B { ... };
class C : public A, public B { ... };
```

4. **Hierarchical Inheritance** → Multiple classes inherit from the same base class.
```cpp
class A { ... };
class B : public A { ... };
class C : public A { ... };
```

5. **Hybrid Inheritance** → Combination of two or more types (e.g., multiple + multilevel).


### Inheritance Ambiguity
Occurs in multiple inheritance when two base classes have functions with the same name.

Example:
```cpp
class A { public: void greet() { cout << "Hello from A"; } };
class B { public: void greet() { cout << "Hello from B"; } };
class C : public A, public B { };

C obj;
obj.greet();   // ❌ Ambiguity: which greet()?
```

Solution: Use scope resolution operator (::):
```cpp
obj.A::greet();   // Calls A’s greet()
obj.B::greet();   // Calls B’s greet()
```

### Why Inheritance?
- **Code Reusability** → Avoid rewriting common properties/methods.
- **Extensibility** → Derived classes can add new features.
- **Readability & Manageability** → Organizes code into logical hierarchies.
- **Polymorphism** → Enables runtime flexibility when combined with virtual functions.

## Polymorphism
### What is Polymorphism?
- **Polymorphism** = "many forms."
- It allows the same function, operator, or method to behave differently depending on the context.
- Real‑life example:  
  - A person can be a **father** to his child, a **husband** to his wife, and a **son** to his parents — same person, different roles.

### Types of Polymorphism
#### A) Compile‑time Polymorphism (Static Polymorphism)
- Behavior is decided at **compile time**.
- Achieved by:
  - **Function Overloading**
  - **Operator Overloading**

1. **Function Overloading**
    - Same function name, different parameter lists (different signatures).
    - Return type alone cannot distinguish overloaded functions.
    
    Example:
    ```cpp
    class Print {
    public:
        void show(int x) {
            cout << "Integer: " << x << endl;
        }
        void show(double y) {
            cout << "Double: " << y << endl;
        }
        void show(string s) {
            cout << "String: " << s << endl;
        }
    };

    int main() {
        Print p;
        p.show(10);        // calls int version
        p.show(3.14);      // calls double version
        p.show("Ninad");   // calls string version
    }
    ```
2. **Operator Overloading**
    - Redefining how operators work for user‑defined types.
    - Not all operators can be overloaded (::, ?:, ., .* cannot be overloaded).
    
    Example:
    ```cpp
    class Complex {
        public:
            int real, imag;

            Complex(int r=0, int i=0) : real(r), imag(i) {}

            // Overload + operator
            Complex operator + (const Complex& other) {
                return Complex(real + other.real, imag + other.imag);
            }
        };

        int main() {
            Complex c1(2, 3), c2(4, 5);
            Complex c3 = c1 + c2;   // uses overloaded +
            cout << c3.real << " + " << c3.imag << "i" << endl;
        }
    ```

#### B) Run-time Polymorphism (Dynamic Polymorphism)
- Behavior is decided at runtime.
- Achieved by method overriding using inheritance + virtual functions.

1. **Method Overriding**
    - Child class redefines a method of the parent class.
    - Method name and parameters must be the same.
    - Requires `virtual` keyword in base class.

    Example:
    ```cpp
    class Animal {
    public:
        virtual void sound() {   // virtual function
            cout << "Animal makes a sound" << endl;
        }
    };

    class Dog : public Animal {
    public:
        void sound() override {   // override base method
            cout << "Dog barks" << endl;
        }
    };

    class Cat : public Animal {
    public:
        void sound() override {
            cout << "Cat meows" << endl;
        }
    };

    int main() {
        Animal* a1 = new Dog();
        Animal* a2 = new Cat();

        a1->sound();   // Dog barks (runtime decision)
        a2->sound();   // Cat meows (runtime decision)

        delete a1;
        delete a2;
    }        
    ```
    - **`virtual` keyword** → Used in a base class to mark a function for runtime polymorphism. It tells the compiler: “this function can be overridden in derived classes, and calls should be resolved at runtime.”
    - **`override` keyword** → Used in a derived class to indicate that a function is overriding a virtual function from the base class. It helps catch errors if the base function signature doesn’t match.

### Why Polymorphism?
- **Flexibility** → same interface, different implementations.
- **Code Reusability** → write generic code that works with multiple types.
- **Extensibility** → add new classes without changing existing code.
- **Readability** → makes code closer to real‑world modeling.


## Abstraction
### What is Abstraction?
- **Abstraction = Implementation hiding.**
- It means showing only the essential features of an object and hiding the internal details.
- The user interacts with the interface (what the object can do), not the implementation (how it does it).
👉 Real‑life example:
- When you drive a car, you use the steering wheel, accelerator, and brake.
- You don’t need to know how the engine, fuel injection, or braking system works internally.

### How is Abstraction Achieved in C++?
1. **Abstract Classes** → Classes that contain at least one pure virtual function.
2. **Interfaces** → In C++, interfaces are implemented using abstract classes with only pure virtual functions.

### Example code
(refer /10_Abstraction.cpp)
- A pure virtual function is declared but not defined in the base class.
- `virtual void sound() = 0;` - It doesn’t mean “assigning a value to a function.” It’s just special syntax telling the compiler: “This function has no implementation here, subclasses must implement it.”
- Why abstract classes can't be instantiated? (Ex - `Animal a; // ❌ Error`)
    - Animal has a pure virtual function (sound()), so it’s incomplete.
    - You cannot create an object of an incomplete class.
    - But you can create pointers or references to it: 
    `Animal* a1 = new Dog();`
    - Here, Dog is a complete class (it implements sound()), so you can instantiate it.
    - The pointer type is Animal* because Dog is‑a Animal (inheritance relationship).
    - This is the essence of runtime polymorphism: you can treat different derived objects (Dog, Cat) as the same base type (Animal) and call their overridden methods.

### Pure virtual functions and Interfaces
- In Java, you have a keyword interface.
- In C++, there is no separate interface keyword.
- Instead, an interface is implemented using an abstract class with only pure virtual functions.
- Example:
```cpp
class IShape {
    public:
        virtual void draw() = 0;   // pure virtual
        virtual void resize() = 0; // pure virtual
};
```
- Derived classes must implement all pure virtual functions:
```cpp
class Circle : public IShape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
    void resize() override {
        cout << "Resizing Circle" << endl;
    }
};
```

👉 So:
- Abstract class = has at least one pure virtual function.
- Interface in C++ = abstract class with only pure virtual functions.
- There’s no keyword interface in C++ — it’s just a design pattern using abstract classes.

### Abstraction vs Encapsulation
![alt text](abstraction_vs_encapsulation.png)
👉 Shortcut to remember:

Encapsulation = Data hiding.

Abstraction = Implementation hiding.

## Friend Function
- Normally, private/protected members are hidden from outside the class.
- Sometimes, you want an external function to access them (e.g., for operator overloading, utility functions).
- Declaring it as a friend breaks the usual access rules and gives that function special permission.

### Key Points
- Declared inside the class with friend keyword.
- Defined outside the class scope.
- Not a member function (so it doesn’t use this pointer).
- Can access private and protected members of the class.
- Friendship is not mutual: if class A declares class B as a friend, B can access A’s private members, but not vice versa

## Friend Class
- A friend class is a class that has access to another class’s private/protected members.
- Declared with friend class ClassName;.

### When to use?
- **Getters/Setters** → Normal controlled access for most cases.

- **Friend Functions** → When you need external functions (like operators or utilities) to access private data.

- **Friend Classes** → When two classes are tightly linked and one needs full access to the other’s internals.

---

### What is Operator Overloading?

Operator overloading is a compile-time polymorphism feature that allows you to redefine how standard operators (like `+`, `-`, `*`, `==`, `<<`, or `[]`) behave when applied to user-defined types (like classes or structs).

Without operator overloading, custom types require named methods:

```cpp
Complex c1(1, 2), c2(3, 4);
Complex c3 = c1.add(c2); // Method call

```

With operator overloading, you can write:

```cpp
Complex c3 = c1 + c2;    // Natural mathematical syntax

```

Under the hood, the compiler translates `c1 + c2` into a call to an overloaded operator function, typically written as:

```cpp
Complex operator+(const Complex& other) const {
    return Complex(this->real + other.real, this->imag + other.imag);
}

```

### Why Does C++ Support It?

Bjarne Stroustrup designed C++ with a foundational principle: **user-defined types should behave like built-in types.**

1. **First-Class Types:** If a built-in `int` or `double` supports `+`, `*`, and `==`, types like `Complex`, `Matrix`, `Vector3D`, or `BigInt` should feel just as native and expressive.
2. **Standard Library Ergonomics:** The standard library relies heavily on it:
* Stream I/O: `std::cout << x;` relies on overloading `<<`.
* Smart Pointers: `std::unique_ptr` and `std::shared_ptr` overload `->` and `*` so they look and feel like raw pointers.
* Containers: `std::vector` and `std::map` overload `[]` for natural indexing.


3. **Domain-Specific Expressiveness:** For graphics, game development, scientific computing, and physics engines, writing vector math as `v1 = v2 * 2.0f + v3;` is far more readable and maintainable than `v1 = v2.multiply(2.0f).add(v3);`.

### Why Doesn't Java Support It?

James Gosling and the designers of Java deliberately excluded user-defined operator overloading. The primary reasons include:

1. **The "Keep It Simple" Philosophy:** Java was designed to reduce developer footguns and cognitive load. In C++, developers occasionally abused operator overloading (for instance, overloading `+` to mean "append to database" or `*` to mean "intersect sets"), which makes code unpredictable.
2. **Clarity and Predictability:** In Java, seeing `a + b` guarantees arithmetic or string concatenation. You never have to worry whether `+` initiates an expensive database query, creates multiple temporary objects, or triggers complex side effects behind the scenes.
3. **Maintenance at Scale:** Java targeted large enterprise codebases where hundreds of engineers collaborate. Explicit method calls like `matrix.multiply(other)` leave zero ambiguity about what operation is taking place.

*(Note: Java has a single built-in operator overload: `+` for `String` concatenation, but developers cannot define their own.)*


### Language Support at a Glance

| Language | User-Defined Operator Overloading? | Approach |
| --- | --- | --- |
| **C++** | Yes | Full support (free functions and member functions) |
| **Python** | Yes | Supported via dunder/magic methods (`__add__`, `__eq__`) |
| **C#** | Yes | Supported via static methods (`public static Vector operator +`) |
| **Java** | No | Only built-in `+` for strings; use methods like `BigDecimal.add()` |
| **JavaScript** | No | Only implicit type coercion (`valueOf`, `Symbol.toPrimitive`) |
| **Go** | No | Deliberately excluded for simplicity and readability |

---

