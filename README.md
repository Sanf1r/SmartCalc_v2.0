# SmartCalc_v2.0

Implementation of SmartCalc v2.0.

Tested on MacOS Big Sur 11.6.6.

Made on June 21 2023 as part of my education in School 21 :)

https://github.com/Sanf1r/SmartCalc_v2.0/assets/100280376/2011a236-8786-4e6f-97b1-14a7e013fc96

## Introduction

This implements an extended version of the standard calculator in C++ in the object-oriented programming paradigm, implementing the same functions as the previously developed application in SmartCalc v1.0 project. In addition to basic arithmetic operations such as add/subtract and multiply/divide, the calculator have the ability to calculate arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.). Besides calculating expressions, it support the use of the _x_ variable and the graphing of the corresponding function. As for other improvements there are a credit calculator and input from keyboard.

## Information

Note that you should use *Dijkstra's algorithm* to translate expressions into *reverse Polish notation* to implement the calculator. You can find all the necessary information in the SmartCalc v1.0 project description to refresh your knowledge.

### MVC pattern

The Model-View-Controller (MVC) pattern is a scheme of separating application modules into three macro-components: a model that contains the business logic, a view that is a UI form to interact with the program, and a controller that modifies the model by user action.

The concept of MVC was introduced by Trygve Reenskaug in 1978, who was working on the Smalltalk programming language at Xerox PARC. Later, Steve Burbeck implemented the pattern in Smalltalk-80.
The final version of the MVC concept was published in the journal Technology Object in 1988. The MVC pattern subsequently evolved, giving rise to variants such as HMVC, MVA, MVVM.

The main need for this pattern stems from the developers' desire to separate the business logic of the program from the views, which makes it easy to replace views and to reuse logic that has been implemented once in other environments. A model separated from the view and a controller to interact with it allows you to reuse or modify already written code more efficiently.

The model stores and accesses the main data, performs operations on requests, defined by the business logic of the program that means it is in charge of the part of the program responsible for all algorithms and information processing. These models, modified by the controller, affect the information display on the user interface. The model in this program should be the class library that performs the calculations. This library must provide all the necessary classes and methods to perform them. And this is the business logic of the program, because it provides the means to solve the problem.

A controller is a thin macro component that performs model modifications. It is used to generate requests for it. In code, it looks like a kind of "facade" for the model that means a set of methods that already work directly with the model. It is called thin because the ideal controller contains no additional logic other than calling one or more methods of the model. The controller serves as a link between the interface and the model. This allows the model to be fully encapsulated from the display. This separation is helpful in that it allows the view code to know nothing about the model code and to address only the controller, whose interface of the provided functions will probably be not changed much. The model, on the other hand, can undergo significant changes, and if you "move" to other algorithms, technologies, or even programming languages in the model, only a small section of code in the controller directly related to the model will need to be changed. Otherwise, it would probably be necessary to rewrite a significant part of the interface code, as it would depend a lot on the implementation of the model. So, when interacting with the interface, the user calls controller methods that modify the model.

The view includes all code associated with the program interface. An ideal interface code should not contain any business logic. It only represents the form for interaction with the user.

