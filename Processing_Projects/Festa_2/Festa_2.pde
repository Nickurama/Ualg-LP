Spinner spinner;
final color RED = color(255, 0, 0);
final color GREEN = color(0, 255, 0);
final color BLUE = color(0, 0, 255);
final color DARK_BLUE = color(0, 0, 128);
final color BLACK = color(0, 0, 0);
final color GREY = color(100, 100, 100);
final color WHITE = color(255, 255, 255);
float timeElapsed;
PImage ualgImage;
PImage fireImage;

boolean isPressingMouse;
float initialMouseX;
float initialMouseY;
float timeElapsedMouse;

void settings()
{
    size(1024, 1024);
}

void setup()
{
    ualgImage = loadImage("logo.png");
    fireImage = loadImage("fire_circle.png");
    timeElapsed = 0;
    spinner = new Spinner(512, 512, 0, 75, DARK_BLUE, BLACK, RED, GREEN, BLUE);
    isPressingMouse = false;
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

void mousePressed()
{
    isPressingMouse = true;
    initialMouseX = mouseX;
    initialMouseY = mouseY;
}

void mouseReleased()
{
    isPressingMouse = false;
    float vectorX = mouseX - initialMouseX;
    float vectorY = mouseY - initialMouseY;
    float intensity = dist(mouseX, mouseY, initialMouseX, initialMouseY) / timeElapsedMouse;

    int signal = 1;

    if (vectorX >= vectorY)
    {
        if (initialMouseY >= spinner.y)
        {
            if (mouseX >= 0)
                signal = 1;
            else
                signal = -1;
        }
    }
    else
    {

    }
    timeElapsedMouse = 0;
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;

    if (isPressingMouse)
    {
        timeElapsedMouse += deltaT;
    }

    spinner.update(deltaT);
}

void draw()
{
    update();

    background(WHITE);

    spinner.draw();

    drawUI();

    drawMouse();
}

void drawMouse()
{
    if (isPressingMouse)
    {
        line(initialMouseX, initialMouseY, mouseX, mouseY);
    }
}

void drawUI()
{
    fill(BLACK);
    textAlign(CENTER, CENTER);
    textSize(75);
    text("spins: " + spinner.spins, 200, 50);
    text("Max RPS: " + spinner.maxRPS, 750, 50);
}