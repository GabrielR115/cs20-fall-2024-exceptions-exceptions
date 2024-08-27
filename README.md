# Exceptions

In this lab we'll add some exception handling to an existing class.

## Part 1: Military Time

Start by examining the `Time` class in `miltime.h`. This class represents a moment in time to the nearest minute using a 12-hour clock (AM/PM). For now it is nothing more than a simple container. Let's make it more interesting by adding some logic to it.

First, check out the unit tests in `miltime_test.cpp`. These tests are designed to exercise the 24-hour, or [military time](https://en.wikipedia.org/wiki/24-hour_clock), features of the `Time` class. You'll notice that the tests do not pass (and in fact do not even compile) because these features have not been written yet. Writing the tests first and the logic second is known as [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development), or TDD.

Let's practice TDD now by adding the necessary logic to make all unit tests pass. You will need to:

1. Add a new constructor that takes a 24-hour clock as input: `Time(int militaryHour, int minute)`. The constructor should convert the given 24-hour time to a 12-hour one and set the object's private members (`hour`, `minute`, `meridian`) accordingly.
2. Add a new public method `Time::getMilitaryHour` that returns the military hour given the object's current state. For example, if the time is 1:30 PM, `getMilitaryHour` would return 13.

After adding these features to `Time`, run the unit tests and make sure they pass. Do not continue until all tests pass.

## Part 2: Bad Parameter Exception

The `Time` class has a problem: It allows any value for the hour and minute, including invalid ones such as -1 or 99. Let's fix that by checking the constructor parameters and throwing an exception if they are invalid. This will guarantee that invalid `Time` objects cannot be created.

Follow these steps:

1. Add a `BadParameterException` class to `miltime.h`. To make the exception class more reusable, make the parameter type generic (`template <typename T>`) so that the parameter types can be changed easily. The class should also have a constructor that takes three parameters: the invalid value and the minimum and maximum allowable values for the parameter (e.g., `BadParameterException(T badParameter, T minimum, T maximum)`). The constructor should copy these values to private member variables.
2. Add public getter methods to `BadParameterException` so that clients of the class can access the `badParameter`, `minimum`, `maximum` attributes.
3. In each of the `Time` class's two constructors, check that each parameter is within the valid range and throw a `BadParameterException` if it is not. (Hint: You can simplify this by adding a private helper method `void Time::checkParam(int param, int min, int max)`.)

Use the `main` function to experiment with `BadParameterException` and make sure it works as expected. Then, in `miltime_test.cpp` add some unit tests for it such as:

* `TEST_CASE("Standard time constructor checks for bad parameters") { ... }`
* `TEST_CASE("Military time constructor checks for bad parameters") { ... }`

You can use the Catch2 macros `REQUIRE_THROWS_AS` and `REQUIRE_NOTHROW` for these tests. (See [Assertion Macros](https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md#exceptions).) For example:

* `REQUIRE_THROWS_AS(Time(24, 0), BadParameterException<int>);`
* `REQUIRE_NOTHROW(Time(12, 59, PM));`

## Part 3: Exception Inheritance

At this point, the `Time` class protects against invalid input by throwing an exception, but the exception isn't very helpful to clients of the `Time` class. Consider this example:

	try {
		Time time(13, 13, AM);
	} catch (const BadNamedParameterException<int>& e) {
		cerr << "Bad parameter: " << e.getBadParameter() << endl;
	}

This will print `Bad parameter: 13` but the exception doesn't explain which parameter is invalid. Let's fix that by extending and enhancing the `BadParameterException` class through inheritance:

1. In `miltime.h`, add a new class called `BadNamedParameterException` that inherits from `BadParameterException`. 
2. Add a private `string` member `name` to hold the name of the invalid parameter.
3. Add a constructor to `BadNamedParameterException` that is identical to `BadParameterException`'s but adds a fourth parameter `string name`. It should set the `name` member and delegate the remaining parameters to its parent class constructor.
4. Add a public `getDescription` method that returns a string explaining the bad parameter, such as "Argument hour must be between 1 and 12 (got 13)". (The exact text is up to you.) _Note: When implementing this method, you may encounter "use of undeclared identifier" errors when invoking a `BadParameterException` method from `BadNamedParameterException`, which is unexpected because a child class should have access to its parent's public members. This error is an unfortunate quirk of the C++ language when using inheritance with templated classes. There are several workarounds, but the easiest is to invoke the method through an explicit `this`, as in `this->getMinimum()`._
5. Test the `BadNamedParameterException` class by creating an invalid `Time` object, catching the exception, and print the value of `getDescription`. (You do not need to write unit tests for `BadNamedParameterException`.)
