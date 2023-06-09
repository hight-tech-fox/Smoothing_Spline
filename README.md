# Smoothing_Spline
In this article, we explore the approximation of functions using a smoothing spline, determine what is affected by the smoothing parameter and the variation of weight coefficients in a discrete scalar product.

<h3>Technical task</h3>
Construct a smoothing spline for the number of observations n=1784, where values are a random variable x with parameters m=1.01, std=3.85.
<h3>Task Analysis</h3>

The array of points was obtained in MS Excel using the formula НОРМОБР(СЛЧИС();M;σ).
Graphs were constructed for various values of the smoothing parameter p. With w=1.0.
On all graphs, black dots are observations, colored dots are a smoothing spline for a given p. To make the point spread more distinct, the values of the observations and the values obtained by the smoothing spline were multiplied by 100 (this changed the scale, but did not affect the overall
graph trends).
т
<h4>При p=0.2:</h4>
https://www.desmos.com/calculator/xkxwquxndk

![qP1P_eltCzw](https://github.com/hight-tech-fox/Smoothing_Spline/assets/106419860/278b4bbb-1b30-4454-b8e7-22028737590e)
