# RSAAnalyzer
RSA Analyzer, based on BigInteger architecture and David Sole's CPC Theoreme (https://www.academia.edu/43396783/Factorizaci%C3%B3n_de_n%C3%BAmeros_semiprimos_a_trav%C3%A9s_del_m%C3%A9todo_de_Conjuntos_de_Par%C3%A1bolas_Conc%C3%A9ntricas_o_CPC)

It performs initial analysis for CPC0, then iterates over all CPC set.
To achieve this, RSAAnalyzer performs fake-parallelism via bat files

This project uses BigInteger.c (https://github.com/DoHITB/BigInteger.c) and Logging.c (https://github.com/DoHITB/Logging.c) projects

           
           
                   +----------------------+
                   |                      |
                   |                      V
                   |              +-----------------+
                   |              | RSAAnalyzer.exe |
                   |              +-------+---------+
                   |                      |
                   |                      |
                   |                  argc == 0
                   |                      |
                   |               +------+------+
                   |               |             |
                   |              yes            no
                   |               |             |
                   |               V             V
                   |        +--------------+  +----------------+                    +------------------------+
                   |        |  get number  |  |   gather data  +------------------> | EQSolver (CUDA Module) |
                   |        +--------------+  +----------------+                    +-------------+----------+
                   |        |   del.bat    |  | check solution | <---------+                      |
                   |        +--------------+  +------+---------+           |                      |
                   |        |    create    |         |                     |                      |
                   |        | waitlist.bat |       solves                  |                      |
                   |        +--------------+         |                     |                      |
             +-----+--------+ waitlist.bat |         |                     |                      |
             |     |        +--------------+         |                     |                      |
             |     |        |   create     |         |                     |                      v
             |     |        |   main.bat   |         |                     |                   Result
             |     |        +--------------+         |                     |
             |     |        |   main.bat   |         |                     |
             |     |        +------+-------+         |                     |
             |     |               |                 |                     |
             |     +---------------+       +---------+--------+            | 
             |                             |                  |            |
             |                            yes                 no           |
             |                             |                  |            |
             |                             V                  V            | 
             |                   +-----------------+    +----------+       |
             |                   | write RSAWL.dat |    | increase |       |
             |                   +---------+-------+    +-----+----+       |
             |                             |                  |            |
             V                             |                  +------------+
    +--------------------+                 |
    |  RSAWaitList.exe   |                 |
    +--------------------+                 |
    | wait for RSAWL.dat |<----------------+
    +--------------------+         
             |
             |
             V
            End


It technically works, thou need some performance enhacement, testing, and some improvements.
