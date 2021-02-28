**Installation**

1. Download OpenSliceDDS Community Edition from: https://github.com/ADLINK-IST/opensplice/releases. We recommend the 6.7.180404OSS for x86_64.linux release (installer version).
2. Create a new folder "OpenSpliceDDS" into your home folder "/home/user"
3. Extract the file downloaded in (1) into the folder created in (2)
4. Open the “release.com” file available at: "/home/user/OpenSpliceDDS/HDE/x86_64.linux/release.com"

```
1	if [ "${SPLICE_ORB:=}" = "" ]
2	then
3	SPLICE_ORB=DDS_OpenFusion_1_6_1
4	export SPLICE_ORB
5	fi
6	if [ "${SPLICE_JDK:=}" = "" ]
7	then
8	SPLICE_JDK=jdk
9	export SPLICE_JDK
10	fi
11	if [ -n "${BASH_VERSION}" ]
12	then
13	OSPL_HOME="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
14	else
15	echo "Please manually set OSPL_HOME to the install directory."
16	fi
17	PATH=$OSPL_HOME/bin:$PATH
19	LD_LIBRARY_PATH=$OSPL_HOME/lib${LD_LIBRARY_PATH:+:}$LD_LIBRARY_PATH
20	CPATH=$OSPL_HOME/include:$OSPL_HOME/include/sys:${CPATH:=}
21	if [ "${OSPL_URI:=}" = "" ]
22	then
23	OSPL_URI=file://$OSPL_HOME/etc/config/ospl.xml
24	export OSPL_URI
25	fi
26	OSPL_TMPL_PATH=$OSPL_HOME/etc/idlpp
27	. $OSPL_HOME/etc/java/defs.$SPLICE_JDK
28	export OSPL_HOME PATH LD_LIBRARY_PATH CPATH OSPL_TMPL_PATH VORTEX_DIR
```
5. Add line 17 as follows:
Edited file:
```
1	    if [ "${SPLICE_ORB:=}" = "" ]
2	    then
3	    SPLICE_ORB=DDS_OpenFusion_1_6_1
4	    export SPLICE_ORB
5	    fi
6	    if [ "${SPLICE_JDK:=}" = "" ]
7	    then
8	    SPLICE_JDK=jdk
9	    export SPLICE_JDK
10	fi
11	if [ -n "${BASH_VERSION}" ]
12	then
13	OSPL_HOME="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
14	else
15	echo "Please manually set OSPL_HOME to the install directory."
16	fi
>> 17	OSPL_HOME="/home/user/OpenSpliceDDS/HDE/x86_64.linux"
18	PATH=$OSPL_HOME/bin:$PATH
19	LD_LIBRARY_PATH=$OSPL_HOME/lib${LD_LIBRARY_PATH:+:}$LD_LIBRARY_PATH
20	CPATH=$OSPL_HOME/include:$OSPL_HOME/include/sys:${CPATH:=}
21	if [ "${OSPL_URI:=}" = "" ]
22	then
23	OSPL_URI=file://$OSPL_HOME/etc/config/ospl.xml
24	export OSPL_URI
25	fi
26	OSPL_TMPL_PATH=$OSPL_HOME/etc/idlpp
27	. $OSPL_HOME/etc/java/defs.$SPLICE_JDK
28	export OSPL_HOME PATH LD_LIBRARY_PATH CPATH OSPL_TMPL_PATH VORTEX_DIR
```
6. Once edited, copy the contents of the previous file at the end of the .bashrc file available at: “/home/user. Note that this file is hidden by default. To make hidden files visible press Ctrl-H.

7. Open a terminal window and execute the following command to build the DDS library:

```
make -C $OSPL_HOME/custom_lib -f Makefile.Build_DCPS_ISO_Cpp2_Lib 
```

8. Open a new terminal, move to the "home/user directory", and execute the following command to clone the GitHub repository:
```git clone https://github.com/DOCGroup/MPC```
9. Open again the .bashrc file, available at: “/home/user, and include the following line at the end:
```export MPC_ROOT="/home/user/MPC"```
10. Open a new terminal and execute the following command to create a new environment variable and update the .bashrc file:
```source .bashrc```
11. Compiling the generated C/C++ code.
The RoQME Data Space (based on DDS) is implemented in C++ and, thus, need to be compiled following the steps indicated next:

- Copy the following code at the end of the .bashrc file, available at: “/home/user, in order to create the ROQME_ROOT, LD_LIBRARY_PATH and CPATH environment variables:

```
export ROQME_ROOT="/home/user/roqme-dds/ 
export LD_LIBRARY_PATH=$ROQME_ROOT/cpp/roqmeDDS/lib:$LD_LIBRARY_PATH
export CPATH=$ROQME_ROOT/cpp/roqmeDDS/include:$ROQME_ROOT/cpp/roqmeDDS/idl:$CPATH
```

12. Move to the generated “roqme-dds” project, available at: “/home/user/roqme/cpp/roqmeDDS”, open a new terminal, and execute the following commands:
```
chmod +x gen_makefile.sh
./gen_makefile.sh
make
```
