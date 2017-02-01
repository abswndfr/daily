### source 



    $ cat mytest.cpp 
    #include <iostream>
    #include <gflags/gflags.h>
    #include <glog/logging.h>

    DEFINE_string(op1, "", "my 1st gflags option");

    int main(int argc, char** argv) {
      std::cout << argc << std::endl;
      std::cout << argv[0] << std::endl;

      // logfile name : argv[0].hostname.userid.log.ERROR.date-time	
      google::InitGoogleLogging(argv[0]);   

      gflags::ParseCommandLineFlags(&argc, &argv, true);
      std::cout << "input " << FLAGS_op1.size() << std::endl;
      LOG(INFO) << "input " << FLAGS_op1.size() << std::endl;

      return 0;
    }


### make 

    $ g++ mytest.cpp -lgflags -lpthread -lglog



## run 

    $ ./a.out -op1 hello
    3
    ./a.out
    input 5


### log 

    $ ll /tmp
    total 160
    -rw-rw-r--  1 ceph ceph   186 Feb  1 14:45 a.out.ceph8.ceph.log.INFO.20170201-144547.10710
    lrwxrwxrwx  1 ceph ceph    47 Feb  1 14:45 a.out.INFO -> a.out.ceph8.ceph.log.INFO.20170201-144547.10710


    $ cat /tmp/a.out.INFO
    Log file created at: 2017/02/01 14:45:47
    Running on machine: ceph8
    Log line format: [IWEF]mmdd hh:mm:ss.uuuuuu threadid file:line] msg
    I0201 14:45:47.316763 10710 mytest.cpp:14] input 5

