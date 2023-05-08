final color BLACK = color(0, 0, 0);

//Playspace Config
final int BUBBLE_SIZE = 50;
final int PADDING = 20;
final int WIDTH_BUBBLES = 10;
final int HEIGHT_BUBBLES = 15;
final int MAX_BUBBLES = 10;

final color WALL_COLOR = color(255, 255, 0);
final color CEILINLG_COLOR = color(100, 100, 100);
final color CANON_COLOR = color(255, 255, 0);
final color PLAYSPACE_COLOR = color(255, 255, 255);

//Bubble colors
final private color ORANGE = color(248, 184, 139);
final private color GREEN = color(186, 237, 145);
final private color RED = color(254, 163, 170);
final private color BLUE = color(178, 206, 254);
final private color PINK = color(255, 192, 203);
final private color PURPLE = color(128, 0, 128);

final private int COLOR_AMMOUNT = 6;
final private color[] COLORS = { ORANGE, GREEN, RED, BLUE, PINK, PURPLE };

//Playspace elements
float timeElapsed;
Cannon cannon;
Ceiling ceiling;
Bubble nextBubble;

void settings()
{
    int w_width = BUBBLE_SIZE * WIDTH_BUBBLES + PADDING * 2;
    int w_height = BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING;
    size(w_width, w_height);
}

void setup()
{
    timeElapsed = 0;
    cannon = new Cannon(PADDING + BUBBLE_SIZE * WIDTH_BUBBLES / 2, PADDING + BUBBLE_SIZE * HEIGHT_BUBBLES - 2 * BUBBLE_SIZE, BUBBLE_SIZE, CANON_COLOR);
    ceiling = new Ceiling(WALL_COLOR, CEILINLG_COLOR, BUBBLE_SIZE, WIDTH_BUBBLES, PADDING, MAX_BUBBLES);
    nextBubble = new Bubble(PADDING + BUBBLE_SIZE * WIDTH_BUBBLES / 2 - 1, 100, BUBBLE_SIZE, PI/4, COLORS[int(random(COLOR_AMMOUNT))]);
}

void keyPressed()
{
    if (keyCode == LEFT)
    {
        cannon.rotateLeft();
    }
    else if (keyCode == RIGHT)
    {
        cannon.rotateRight();
    }
    else if (key == ' ' || keyCode == UP)
    {
        //TODO: SHOOT
        println("pew pew! :3");
    }
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;
    
    cannon.update(deltaT);
    ceiling.update(deltaT);
    b.update();
}

void draw()
{
    update();
    
    drawPlaySpace();
    cannon.draw();
    ceiling.draw();
    b.draw();
}

void drawPlaySpace()
{
    background(WALL_COLOR);
    rectMode(CORNER);
    noStroke();
    fill(PLAYSPACE_COLOR);
    rect(PADDING, 0, BUBBLE_SIZE * WIDTH_BUBBLES, BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING);
}