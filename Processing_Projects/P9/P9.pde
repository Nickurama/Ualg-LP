final color DARK_RED = color(128, 0, 0);
final color DARK_GREEN = color(0, 128, 0);

final int W_WIDTH = 720;
final int W_HEIGHT = 720;

private TrafficLight tl;
private Car car;

void settings()
{
    size(W_WIDTH, W_HEIGHT);
}

void setup()
{
    tl = new TrafficLight(300, 300, 100, 0);
    tl.switchGreen();
    car = new Car(450, 450, 100, 45, DARK_RED, 0, 5);
}

void draw()
{
    background(DARK_GREEN);
    
    if (keyPressed)
    {
        tl.toggle();
        car.toggleMovement();
    }
    
    tl.draw();
    car.draw();
}