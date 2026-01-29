# Computer Science I
## Lab 11.0 - Encapsulation & Structures
[School of Computing](https://computing.unl.edu)  
[College of Engineering](https://engineering.unl.edu/)  
[University of Nebraska-Lincoln](https://unl.edu)  
[University of Nebraska-Omaha](https://unomaha.edu)

This lab introduces encapsulation and structures in C.

## Prior to Lab

* Read and familiarize yourself with this handout.
* Read the required chapters(s) of the textbook as
  outlined in the course schedule.

In addition, you may want to:

* Read Chapters 10 and 23 of the [Computer Science I](http://cse.unl.edu/~cbourke/ComputerScienceOne.pdf) textbook
* Watch Videos 11.1 thru 11.3 of the [Computer Science I](https://www.youtube.com/playlist?list=PL4IH6CVPpTZVkiEnCEOdGbYsFEdtKc5Bx)
  video series

### Peer Programming Pair-Up

**For students in the online section:** you may complete the lab on your
own if you wish or you may team up with a partner of your choosing.  You
may consult with a lab instructor to get teamed up online (via Zoom).

**For students in the face-to-face section:** your lab instructor will
team you up with a partner.

To encourage collaboration and a team environment, labs are be
structured in a *peer programming* setup. At the start of each lab, you
will be randomly paired up with another student (conflicts such as
absences will be dealt with by the lab instructor). One of you will be
designated the *driver* and the other the *navigator*.

The navigator will be responsible for reading the instructions and
telling the driver what to do next. The driver will be in charge of the
keyboard and workstation. Both driver and navigator are responsible for
suggesting fixes and solutions together. Neither the navigator nor the
driver is "in charge." Beyond your immediate pairing, you are encouraged
to help and interact and with other pairs in the lab.

Each week you should alternate: if you were a driver last week, be a
navigator next, etc. Resolve any issues (you were both drivers last
week) within your pair. Ask the lab instructor to resolve issues only
when you cannot come to a consensus.

Because of the peer programming setup of labs, it is absolutely
essential that you complete any pre-lab activities and familiarize
yourself with the handouts prior to coming to lab. Failure to do so will
negatively impact your ability to collaborate and work with others which
may mean that you will not be able to complete the lab.

### Lab Objectives & Topics

At the end of this lab you should be familiar with the following

-   Be familiar with the concepts of encapsulation & modularity

-   Understand how to design, declare, and use C structures (both by
    reference and by value)

-   Have some exposure to distributed computing, the client-server
    model and data processing using JavaScript Object Notation (JSON)

## 2. Background

### 2.1 Structures in C

When modeling data, an "entity" may be composed of several different
pieces of data. A person for example may have a first and last name
(strings), an identifier (integer), a birthdate (some date/time representation),
etc. It is much easier and more natural to *group* each of these pieces
of data into one entity. This is a concept known as *encapsulation*--a
mechanism by which data can be grouped together to define an entity.

The C programming language provides a mechanism for encapsulation
using structures. Structures are user defined types that have one or
more data fields--variables which have a type and a name. To access the
member fields of a structure you can use the dot operator; example: .
`student.firstName`.  However, when you have a reference (pointer) to a
structure, you need to use the arrow operator: `student->firstName`.

### 2.2 Distributed Computing & The Client/Server Model

Distributed computing involves multiple machines or devices working together
to solve a problem or perform a task.  Typically, these computers communicate
and coordinate their efforts using a network.  One architectural pattern
in distributed computing is the *client-server* model.  Typically the *server*
provides resources, services, or data to the *client*.  The client makes
*requests* over the network, the server *responds* to those requests.  This
means that the data can be stored on one computer while being processed on
a different one, distributing the different tasks.

For this lab, our example will be the United States Geological Survey's (USGS)
[Earthquake Notification Service](https://earthquake.usgs.gov/earthquakes/feed/v1.0/geojson.php)
which provides live data on earthquakes across the globe.  The server uses
an Application Programmer Interface (API) that clients (our program) can
request data on earthquakes detected in the last hour, day, or week.  The
data is served in a response using the JavaScript Object Notation (JSON) data
format, a universal key-value pair format.  An example of this format has
been provided in `earthquake_data/data/local_data.json`.  Here is a small example
using student data:

```json
{
  "student": {
    "firstName": "John",
    "lastName": "Smith",
    "NUID": 12345678,
    "GPA": 3.5,
    "birthdate": "1970-01-01"
  }
}
```

We have provided most of the code to connect to the USGS's server
and process the JSON data.  Your task will be to design and implement
a C structure that represents this data and then write code that
produces some reports on the data.

## 3. Activities

### 3.1 Getting Started

Clone the project code for this lab from GitHub by using the following
URL: <https://github.com/cbourke/CSCE155-C-Lab11>.

In addition, you may need to install some libraries to complete this
activity.  Run the following commands:

```bash
sudo apt-get update
sudo apt-get install libjson-c-dev
sudo apt-get install libcurl4-gnutls-dev
```

### 3.2 `Student` Structure Demo

To demonstrate how to define and use a structure, we have provided a
completed program (see the files in the `studentDemo` directory)
with a full structure definition to model a student.
Several functions have been implemented to assist in the construction
and printing of this structure. In particular there are two "factory"
functions that can be used to help in the construction of an individual
structure. The factory function takes the appropriate parameters, allocates
memory for a new `Student` instance and sets each field of the structure
appropriately. In the case of strings, `malloc` is used to create enough
space and the string is then copied. The `birthDate` is handled specially:
it parses the date string and creates a `struct tm` which is a *time* structure
defined by the time library (`time.h`). Finally, a pointer to the new
`Student` structure is returned. There is also a print function that takes
a student (by reference) and prints it out to the standard output.

#### Instructions

1.  Examine the syntax and program structure and observe how each
    factory function works as well as how they are used.

2.  Change the values in the function to your name, NUID, and birth
    date.

3.  Compile and run the program using the following commands.

    ```text
    gcc -c student.c
    gcc student.o studentDemo.c
    ```
    Run your program and observe the results. Refer back to this
    program in the next activity as needed.

### 3.3 Designing Your Structure

Under the `earthquake_data` directory we have provided substantial
starter code.  You'll need to design and implement a structure to
represent an earthquake, including the following items:

* An ID (a unique alphanumeric string)
* Location Name
* Magnitude (measured on a Richter scale, [-1.0, 10.0])
* Significance (the impact or damage it had; an integer on the scale [0, 1000])
* A unix timestamp (a `long` integer value corresponding to the time of the earthquake)
* Latitude (a `double` corresponding to the latitude, [-90, 90])
* Longitude (a `double` corresponding to the longitude, [-180, 180])
* Depth (a `double` corresponding to the depth of the earthquake in kilometers)

#### Instructions

Design and implement the `EarthquakeData` structure in the `earthquake.h` header file.

### 3.4 Supporting Your Structure

It is much easier to use structures if you have a collection of supporting
utility functions that allow you to create (factory functions) and format
them in a human readable manner.  

#### Instructions

Implement the following functions in `earthquake.c` as the documentation in the
header file indicates.

* `initEarthquakeData()`
* `createEarthquakeData()`
* `earthquakeDataToString()`

### 3.5 Processing Your Data

Now that we have our structure, we need to process the data that it represents.
In the `runReports()` function we have provided two examples that search
the data for (and print) the weakest (with respect to magnitude) and strongest earthquakes
in the data set.  The first uses an index to keep track of `EarthquakeData`
while the second uses a pointer to a structure.  

##### Compiling & Running

The project code we've provided is a bit more complicated than usual
and so we have provided a `makefile` to build it.  To build the project
simply use `make` in the `earthquake_data` directory.  This will build
an executable called `run`.  You can provide a command line argument to
the program to pull data from the last `hour`, `day`, or `week` using
those keywords.  For example, you could pull all data from the last week
using:

`./run week`

Another option is to use `local` which will load static data from the file
`data/local_data.json` (this is usually done when developing or troubleshooting
so that we don't hit the server with too many requests).

#### Instructions

Add code in the `runReports` function to find the earthquake in the
data set that occurred closest to Lincoln, Nebraska (using the
latitude/longitude values 40.806862, -96.681679).  We have provided
a convenience function, `airDistance()` that you can use.

## 4. Handin/Grader Instructions

1.  Hand in your completed files:

    - `earthquake.h`
    - `earthquake.c`

    and verify it compiles and works through the grader.

2.  Even if you worked with a partner, you *both* should turn in all
    files.

## Advanced Activity (Optional)

1.  An older version of this lab used RSS data feeds (see the `rss`
    directory).  Try to get it working as well!  You'll need to install
    the XML library:

    `sudo apt-get install libxml2-dev libxslt1-dev`

2.  Learn more about cURL and json-c, the libraries used in this lab here:
    * cURL: https://everything.curl.dev/libcurl/index.html
    * json-c: https://github.com/json-c/json-c/wiki
    * Documentation: https://json-c.github.io/json-c/json-c-0.10/doc/html/index.html
