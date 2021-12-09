<h2>Getting Started</h2>

1. Clone

```
git clone https://github.com/BikeLinc/BuildTool
```

2. Build
```
make
```

3. Run
```
make run
```

<br>
<h2>Features</h2>

Currently Supported
- variable declaration
- variable refrencing
- rule creation w/dependencies
- dependency prioritized execution
- circular dependency detection

Planned
- Wildcard Functionality
- Improved Parser

<br>
<h2>Syntax</h2>

Variable Definition
```
<NAME> = "<VALUE>"
```

Variable Referencing
```
$(<NAME>) is reduced to <VALUE>
```

Rule Definition
```
<NAME> : <DEPENDENCY1> <DEPENDENCY2> <DEPENDENCY3>
    <COMMAND>
    <COMMAND>
