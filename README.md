# Welcome to BuildTool

BuildTool is a specification for writing and executing shell rules in a dependency prioritized fashion and is based on GNU's make build tool.

<br>

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

BuildTool currently only supports variable declaration, the referencing of said variables, rule declaration, and dependency prioritized execution.

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
