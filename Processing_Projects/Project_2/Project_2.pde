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
    ceiling = new Ceiling(WALL_COLOR, CEILINLG_COLOR, BUBBLE_SIZE, WIDTH_BUBBLES, PADDING, MAX_BUBBLES);
    cannon = new Cannon(PADDING + BUBBLE_SIZE * WIDTH_BUBBLES / 2, PADDING + BUBBLE_SIZE * HEIGHT_BUBBLES - 2 * BUBBLE_SIZE, BUBBLE_SIZE, CANON_COLOR);
    cannon.loadBubble(new Bubble(0, 0, BUBBLE_SIZE));
    nextBubble = new Bubble(PADDING + BUBBLE_SIZE * WIDTH_BUBBLES / 2 - 2 * BUBBLE_SIZE, PADDING + BUBBLE_SIZE * HEIGHT_BUBBLES - 2 * BUBBLE_SIZE, BUBBLE_SIZE);
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
        cannon.shoot();
        cannon.loadBubble(nextBubble);
        nextBubble = new Bubble(PADDING + BUBBLE_SIZE * WIDTH_BUBBLES / 2 - 2 * BUBBLE_SIZE, PADDING + BUBBLE_SIZE * HEIGHT_BUBBLES - 2 * BUBBLE_SIZE, BUBBLE_SIZE);
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
    nextBubble.update();
}

void draw()
{
    update();
    
    drawPlaySpace();
    cannon.draw();
    ceiling.draw();
    nextBubble.draw();
}

void drawPlaySpace()
{
    background(WALL_COLOR);
    rectMode(CORNER);
    noStroke();
    fill(PLAYSPACE_COLOR);
    rect(PADDING, 0, BUBBLE_SIZE * WIDTH_BUBBLES, BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING);
}