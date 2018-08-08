Project: 90Meter PKCS11 Java Interfaces

Author: Chad Krauthamer

Date created: 07/09/2018

Purpose: This project establishes a connection with the 90Meter
litPKCS11.dll and uses it to read certificates from an inserted SmartCard
within a supported SmartCard reader. This program is built with JDK 8
and works well with Java(TM) SE Runtime Environment(8.0_171-b11)
(build 1.8.0_171-b11).

Issues: The slot index is static, the slot that is checked is at index 0.
Java began depreciating sun.* packages which may cause the program to
create an error log. The program may create an error log for Internal
Error (0xc000000d), but this should not affect the program. It occurs at
[ntdll.dll+0x95415] and is likely caused by an issue within the JVM.


For more information about using sun packages, please see:

http://www.oracle.com/technetwork/java/faq-sun-packages-142232.html
