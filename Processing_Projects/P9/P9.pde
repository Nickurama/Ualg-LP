final color DARK_RED = color(128, 0, 0);
final color DARK_GREEN = color(0, 128, 0);

final int W_WIDTH = 1080;
final int W_HEIGHT = 1080;

private Lane lane;

void settings()
{
    size(W_WIDTH, W_HEIGHT);
}

void setup()
{
    lane = new Lane(540, 540, W_WIDTH, 0);
    // tl = new TrafficLight(300, 300, 100, 0);
    // tl.switchGreen();
    // car = new Car(450, 450, 100, 45, DARK_RED, 0, 5, 0.05);
}

void draw()
{
    background(DARK_GREEN);
    
    lane.draw();
}