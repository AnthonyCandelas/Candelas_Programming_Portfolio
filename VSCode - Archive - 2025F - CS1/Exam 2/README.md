FloodUtils (Java) - Exam 2

Files:
- FloodUtils.java : Java implementation of the flood utility functions.

Description:
This repository contains two implementations (C and Java) of the same
Flood Utilities used for Exam 2. The Java file `FloodUtils.java` provides:
- convertFlow(List<Double>) -> List<Double>
- floodCapacity(double[][], double) -> double

Behavior & error handling (Java):
- convertFlow returns null if the input is null or contains any null element.
- floodCapacity returns Double.NaN if the elevations array is null, empty,
  or contains a null row pointer.

How to compile and run (Java):
1) Compile FloodUtils.java and a small test runner (optional):
   javac -d . FloodUtils.java FloodUtilsTest.java
   java unl.soc.FloodUtilsTest

2) If you only want to compile FloodUtils.java (and use it from other code):
   javac -d . FloodUtils.java

Notes:
- The Java classes use the package `unl.soc`. The `-d .` option tells
  javac to emit class files in the appropriate `unl/soc` directory.
- I tested the Java implementation locally; it produced the expected
  flood capacity of 3.50 for the example grid in the prompt.

Style:
Follow the project's STYLE.md for header and documentation conventions.
