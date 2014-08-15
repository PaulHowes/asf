# ASF

Advanced string formatter for C++

# Building

The Advanced String Formatter is distributed only as a header. There is nothing to compile in this
repository other than tests which also illustrate how to use ASF.

## Dependencies

* [CMake](http://www.cmake.org) 2.8.12 or newer
* C compiler. The following have been tested:
  * [llvm](http://llvm.org) 3.4 or newer
  * [gcc](http://gcc.gnu.org) 4.8.3 or newer
  * [Visual Studio](http://www.visualstudio.com)

## Instructions

I highly recommend building outside of the source tree so that build products do not pollute the
repository. The simplest way to accomplish this is to create a sub-directory named "build" as
follows:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

# Examples

ASF uses a pattern similar to that of C# or Python: a pair of curly braces that contain text which
denotes a placeholder. The characters inside of the placeholder determine what to displayed and how
it is displayed.

For positional and printf uses, the placeholder must be a number that is used as the index into the
vector or list of values to format.

**Note**: Named parameters can be used only when a `std::map` contains the parameter values.

## Positional (printf-style)

    std::cout << asf::format("{0} {1} {2}", "string", 1, 3.3) << std::endl;

    Output:
    hello 1 3.3

## Positional

    std::vector<boost::any> args;
    args.push_back("hello");
    args.push_back(1);
    args.push_back(3.3);
    std::cout << "{0} {1} {2}" % args << std::endl;
    
    Output:
    hello 1 3.3

## Named

    std::map<std::string, boost::any> args;
    args["first"]  = "string";
    args["second"] = 1;
    args["third"]  = 3.3;
    std::cout << "{first} {second} {third}" % args << std::endl;

    Output:
    hello 1 3.3

# TODO List

1.  Remove dependency on `Boost::any`

    There's nothing inherently wrong with `Boost::any`, but I'd prefer to not depend on such a
    large library for one thing. Also the performance of `Boost::any` is known to be poor, so any
    replacement must be benchmarked against it.

2.  Add formatting information to the parameters

    Formatting information should take the form {0:d} where the colon is the separator between the
    positional argument and the characters after it define how to emit the matching argument.

# Contributing

1.  Fork it
2.  Create a feature branch (`git checkout -b new-feature`)
3.  Commit changes (`git commit -am "Added new feature xyz"`)
4.  Push the branch (`git push origin new-feature`)
5.  Create a new pull request.

# Maintainers

* Paul Howes (http://github.com/PaulHowes/)

# License

Advanced String Formatter copyright 2014 Paul Howes and is licensed under the
[Apache License](LICENSE).
