**Installing Instructions**

To build the code in your system, use the following command:
```
make
```

You need to have C++ 11 installed in your system to build the code.

To run the NetworkGen, use following command:

```
./run1.sh arg1 arg2 arg3
where:
arg1 is input file to set environment
arg2 is the units of time to simulate from beginning
arg3 is the time
```

For example:
```
./run1.sh SocialNetworkEnv.inp -y 5
```
This runs the simulation for 5 years

```
./run1.sh SocialNetworkEnv.inp -d 100
```
This runs the simulation for 100 days

Possible choices for argument 2 are: -d (days), -y (years), -h (hours), -m (minutes), -s (seconds) and -w (weeks)

To run the Gyani, simply use the command:
```
./run2.sh
```

**Developers**

Rohit Pruthi

Kunal Singhal

Anshul Bawa
