# EM-clustering
clustering algorithm in order to compress images


In this project, I implemented expectation maximization algorithm on images.Required packages and a simple tutorial to run the code are discussed in the following lines:



To implement this project I used armadillo and opencv libraries.


How to install opencv: [here](https://www.learnopencv.com/install-opencv3-on-ubuntu/)

How to install armadillo: [here](http://www.uio.no/studier/emner/matnat/fys/FYS4411/v13/guides/installing-armadillo/)

If the libraries are installed compile and run the project:

```bash
make
./em
```

As you can see there is a sample picture "Lenna.png" in the project which is obviously the target picture for em

to modify the clustering you should open main.cpp and change the following code:

```bash
EM("Lenna.png",2).execute();
```

the first argument is the path to the image you want to cluster and the second argument is the number of clusters






Good Luck,
