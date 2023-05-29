Spinner spinner;
final color RED = color(255, 0, 0);
final color GREEN = color(0, 255, 0);
final color BLUE = color(0, 0, 255);
final color DARK_BLUE = color(0, 0, 128);
final color BLACK = color(0, 0, 0);
final color GREY = color(100, 100, 100);
final color WHITE = color(255, 255, 255);
float timeElapsed;

void settings()
{
    size(1024, 1024);
}

void setup()
{
    timeElapsed = 0;
    spinner = new Spinner(512, 512, 0, 75, DARK_BLUE, BLACK, RED, GREEN, BLUE);
}

void keyPressed()
{
    if (keyCode == LEFT)
    {
        spinner.rotationSpeed = -15 * 2 * PI;
    }
    else if (keyCode == RIGHT)
    {
        spinner.rotationSpeed = 15 * 2 * PI;
    }
    else if (keyCode == '1')
    {
        spinner.tip1.circleColor = WHITE;
        spinner.tip2.circleColor = RED;
        spinner.tip3.circleColor = GREEN;
    }
    else if (keyCode == '2')
    {
        spinner.tip1.circleColor = RED;
        spinner.tip2.circleColor = GREEN;
        spinner.tip3.circleColor = BLUE;
    }
    else if (keyCode == '3')
    {
        spinner.tip1.circleColor = BLUE;
        spinner.tip2.circleColor = WHITE;
        spinner.tip3.circleColor = BLACK;
    }
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;

    spinner.update(deltaT);
}

void draw()
{
    update();

    background(WHITE);
    spinner.draw();
}