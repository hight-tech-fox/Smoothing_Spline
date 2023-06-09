# Smoothing_Spline
In this article, we explore the approximation of functions using a smoothing spline, determine what is affected by the smoothing parameter and the variation of weight coefficients in a discrete scalar product.

<h2>Technical task</h2>
Construct a smoothing spline for the number of observations n=1784, where values are a random variable x with parameters m=1.01, std=3.85.
<h2>Task Analysis</h2>

The array of points was obtained in MS Excel using the formula НОРМОБР(СЛЧИС();M;σ).
Graphs were constructed for various values of the smoothing parameter p. With w=1.0.
On all graphs, black dots are observations, colored dots are a smoothing spline for a given p. To make the point spread more distinct, the values of the observations and the values obtained by the smoothing spline were multiplied by 100 (this changed the scale, but did not affect the overall
graph trends).
т
<h3>При p=0.2:</h3>
https://www.desmos.com/calculator/xkxwquxndk

![qP1P_eltCzw](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/278b4bbb-1b30-4454-b8e7-22028737590e)

<h3>При p=0.4:</h3>
https://www.desmos.com/calculator/eno0d0xhc9

![9lM5pi0eYE4](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/139f1c86-2c2c-476b-8dff-e335de1a4ce5)

<h3>При p=0.6:</h3>
https://www.desmos.com/calculator/3qpq6ld2dn

![p6p8hTnVBd0](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/a90306cb-f86e-41ec-af55-d8f15c47cc43)

<h3>При p=0.8:</h3>
https://www.desmos.com/calculator/ddsdddyomx

![7KTvgsidbzc](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/3897f1ce-3dff-46fa-9494-73fb64eec30f)

Note that with an increase in the smoothing parameter p, the resulting graph is pressed closer to the x-axis and smoothed out. We get that the higher the smoothing parameter, the higher the error and, consequently, the lower the accuracy. It can be assumed that as p tends to unity, the resulting graph will tend to
straight (straight).
<br></br>
Consider the data on a smaller number of observations, while retaining the first generated random variables x. The number of observations is 10. Graphs are plotted at w=1.0.

https://www.desmos.com/calculator/2jwcyiixpv

![V198dWUDjSw](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/463647a1-4620-4156-80d7-1819eb403765)

Indeed, at a given smoothing setting p, the graph becomes smoother, the speed error. At 0.99 (while aiming for 1) we have practically gained access. Also, when setting, the smoothing of the spline values is selected.
<br></br>
We investigate the dependence of the graph on the weight parameters at p=0.2.

![QZJ3J2rvD04](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/d4184377-90cb-444c-85fa-4015b76fdc9f)

Note that with increasing weight, the resulting graph is more accurate at the nodal points, while being less smooth. As the weight decreases, we see a decrease in accuracy at the nodal points, with more smoothing. As w tends to 0, it cannot be said that the graph will be straightened, we observe a similar graph as at p=0.8 and w=1.0, but with less smoothness.

Thus, we can say that the weights are responsible for the accuracy at the nodal points.
And we can observe the straightest line when p tends to 1 and w tends to 0.

![3UHNWnas7vc](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/9a10b79f-9c26-4ab9-94b1-31ed08b1b3e2)

