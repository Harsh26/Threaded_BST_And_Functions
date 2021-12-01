***How To Run .cpp FILE***

Pre-Requisites: 

Please ensure that "Binary_Search_Tree.cpp" File is placed in easily accessible location.
For Example- 
                     Place it here-------->   D:\Binary_Search_Tree.cpp

Running commands:

1. Use the Run option in any C++ IDE to run above .cpp file.

2. You will be prompted to ***Menu Driven Mode*** Screen.

3. Choose any option between 1-11. And see output in terminal for all options Except option (10) Print Tree.

4. For printing, Please take absolute precautions. Note that after printTree function call, a DOT file will be generated in same location.
    According to above Example DOT file will be in:
                                                                   --------->   D:\myfile.gv. 

    This DOT file will be generated once you try printing.


Steps to visualize "myfile.gv":

     A) Ensure that graphviz is installed in your machine.

     B) Go to cmd. And then to "myfile.gv" file location. In above example(through cmd) go to 
                                                          ---------->    D:\        

                                                         

      C) Write command in following format-

                                    D:\> "dot executable location in your computer" -Tpng <filename.gv> -o <newfilename.png>

   For above example in my pc :

                            -----> D:\> "C:\Program Files\Graphviz2.38\bin\dot.exe" -Tpng myfile.gv -o myfile.png  

D) Open png image to see output.