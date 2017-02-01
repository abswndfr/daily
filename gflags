
### https://gflags.github.io/gflags/ => How To Use gflags (formerly Google Commandline Flags)


### defining flags
    
    DEFINE_<data_type>(<variable_name>, "<default_value>", "<help_string>")


### accessing flags

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    FLAGS_<variable_name>.size() << std::endl;


### source 

    $ cat mytest.cpp 

    #include <iostream>
    #include <gflags/gflags.h>

    DEFINE_string(op1, "", "my 1st gflags option");

    int main(int argc, char** argv) {

      gflags::ParseCommandLineFlags(&argc, &argv, true);
      std::cout << "input " << FLAGS_op1.size() << std::endl;

      return 0;
    }


### make 

    $ g++ mytest.cpp -lgflags -lpthread


### run 

    $ ./a.out -op1 hello11111asdfasdf
    input 18


    $ ./a.out -help
    a.out: Warning: SetUsageMessage() never called

      ...

      Flags from mytest.cpp:
        -op1 (my 1st gflags option) type: string default: ""



### install gflags 

    $ tar xzf gflags-$version-source.tar.gz
    $ cd gflags-$version
    $ mkdir build && cd build
    $ ccmake ..
    
      - Press 'c' to configure the build system and 'e' to ignore warnings.
      - Set CMAKE_INSTALL_PREFIX and other CMake variables and options.
      - Continue pressing 'c' until the option 'g' is available.
      - Then press 'g' to generate the configuration files for GNU Make.
    
    $ make
    $ make test    (optional)
    $ make install (optional)

