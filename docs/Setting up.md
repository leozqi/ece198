## Download the dev tools required

Go to ST.com and download the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html). This is the integrated development environment recommended by the ECE198 LEARN STM32F401RE guide.

Install the appropriate version for your operating system.

### macOS

If your application refuses to open with the message `“STM32CubeIDE” is damaged and can’t be opened`, run the command `xattr -c` to the location of the downloaded application

```sh
xattr -c /path/to/STM32CubeIDE.app
```

## Start a project

When the STM32CubeIDE opens, specify this cloned repository as your workspace and import the `project` subfolder into the IDE. It will already have all the metadata needed by the STM32CubeIDE to identify our board (NUCLEO-F401RE).

As a reference, see page 25 of the [STM32F401RE Guide](https://learn.uwaterloo.ca/d2l/le/content/827236/viewContent/4524395/View) on LEARN.
