---
layout: post
title:  "Compile MySQL C++ connector 1.1.8 on VS 2015 & Win10"
date:   2017-04-17 15:31 +0800
categories: jekyll update
---
#### Compile MySQL C++ connector 1.1.8 on VS 2015 & Win10

***
##### Downloadable binary connector of 1.1.8 is not compatible with VS 2015
This can be inferred from linking errors about _MSC_VER [LNK2038](https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=ZH-CN&k=k(LNK2038)&rd=true).
It should be using VS 2013 according to _MSC_VER mentioned in error msg. I don't want VS 2013 on my laptop. So, I got compile connector from source code.

##### Get the source code
Git repo: https://github.com/mysql/mysql-connector-cpp.git  
use : ```git checkout 1.1.8``` to get the 1.1.8 source code.
Default version that code repo contains is 2.0, which works with MySQL 5.7 and above. I don't want download that. If you are using that version, see this link:
[Build C++ connector of 2.0](https://dev.mysql.com/doc/dev/connector-cpp/building.html).

##### Deal with CMake
Use this : ```cmake -G "Visual Studio 14 2015 Win64"    -DMYSQLCLIENT_STATIC_LINKING=yes ..``` to generate solution file.
Here is a static library. But before that, some modifications must be made. 
1. Add these in CMakeLists.txt. Do alter the paths.
```angular2html
SET(BOOST_ROOT "f:/boost_1_64_0")
SET(MYSQL_DIR "F:/mysql-5.6.26-winx64")
SET(MYSQL_VERSION "5.6.26")
```
MYSQL_VERSION cannot be inferred from try_run block in FindMySQL.cmake. I added some message statement around this block:
```
if(MYSQL_INCLUDE_DIR)
  message("!!!!!!!!!!!!!!!!!!MYSQL_INCLUDE_DIR   ${MYSQL_INCLUDE_DIR}")
endif()
if(NOT MYSQL_VERSION)
  message("!!!!!!!!!!!!!!!!!!MYSQL_VERSION   ${MYSQL_VERSION}")
endif()
if(MYSQL_INCLUDE_DIR AND NOT MYSQL_VERSION)
message("lalal")
  # Write the C source file that will include the MySQL headers
  set(GETMYSQLVERSION_SOURCEFILE "${CMAKE_CURRENT_BINARY_DIR}/getmysqlversion.c")
  file(WRITE "${GETMYSQLVERSION_SOURCEFILE}"
       "#include <mysql.h>\n"
       "#include <stdio.h>\n"
       "int main() {\n"
       "  printf(\"%s\", MYSQL_SERVER_VERSION);\n"
       "}\n"
  )

  # Compile and run the created executable, store output in MYSQL_VERSION
  try_run(_run_result _compile_result
    "${CMAKE_BINARY_DIR}"
    "${GETMYSQLVERSION_SOURCEFILE}"
    CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${MYSQL_INCLUDE_DIR}"
    RUN_OUTPUT_VARIABLE MYSQL_VERSION
  )
message("${CMAKE_BINARY_DIR}" "${GETMYSQLVERSION_SOURCEFILE}")
#  if(_run_result)
    message("!!!!!!!!!!!!!!!!!!_run_result   ${_run_result}")
#  endif()
#    if(_compile_result)
    message("!!!!!!!!!!!!!!!!!!_compile_result   ${_compile_result}")
#  endif()
```
It turned out that compilation is failed. Since I'm not familiar with CMake try_run, I decide to go around that.
Just paste the version from mysql_version.h to CMakeList.txt.

##### Deal with snprintf link error
As listed in VS, comment out ```#define snprintf ....``` in my_config.h(in MySQL Server's include dir).
No need to change this in mysql_private_iface.h, cause VS 2015's VER is 1900:
```angular2html
#if ( defined(_WIN32) || defined(_WIN64) ) && !defined(snprintf) && (_MSC_VER < 1900)
#define snprintf _snprintf
#endif
```
##### Build And Get mysqlcppconn-static.lib
Right click mysqlcppconn-static and build. In my case, file resides in F:\repo\mysql-connector-cpp\build\driver\Release.
Copy and move it to a specific folder.

##### Build Application
I used headers in previous binary distribution but with this newly built lib. Refer to this [post](https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-apps-windows-visual-studio.html) on setting up.
Change C/C++->Code generation -> runtimellbrary to /MT from /MD if encounter linking errors.

##### Do test
Start MySQL server and run compiled application. I copied libmysql.dll to the same folder with generated binary. The app can run now, but not by luck.

##### Done