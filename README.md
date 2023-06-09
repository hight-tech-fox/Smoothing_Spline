# Smoothing_Spline
In this article, we explore the approximation of functions using a smoothing spline, determine what is affected by the smoothing parameter and the variation of weight coefficients in a discrete scalar product.

<h3>Technical task</h3>
Construct a smoothing spline for the number of observations n=1784, where values are a random variable x with parameters m=1.01, std=3.85.
<h3>Task Analysis</h3>

The array of points was obtained in MS Excel using the formula НОРМОБР(СЛЧИС();M;σ).
Graphs were constructed for various values of the smoothing parameter p. With w=1.0.
On all graphs, black dots are observations, colored dots are a smoothing spline for a given p. To make the point spread more distinct, the values of the observations and the values obtained by the smoothing spline were multiplied by 100 (this changed the scale, but did not affect the overall
graph trends).

<h4>При p=0.2:</h4>
https://www.desmos.com/calculator/xkxwquxndk
![image](https://sun9-63.userapi.com/impg/a55xRGDxQUWe_xxHdshXBuaEOyCjQphQrNyEQA/qP1P_eltCzw.jpg?size=961x1201&quality=96&sign=bdd517f91420704edcc05a4a44287dc1&type=album)
![image](https://user-images.githubusercontent.com/98911288/204526168-1a87b54b-74b7-41ed-9b92-397288aa036e.png)
