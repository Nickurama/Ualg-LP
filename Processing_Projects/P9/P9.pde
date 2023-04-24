final int W_WIDTH = 1080;
final int W_HEIGHT = 1080;

Intersection intersection;

void settings()
{
    size(W_WIDTH, W_HEIGHT);
}

void setup()
{
    intersection = new Intersection(W_WIDTH, W_HEIGHT);
}

void draw()
{
    intersection.draw();
}