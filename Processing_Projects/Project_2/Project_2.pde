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

final float RELOAD_TIME = 0.5;

int windowWidth;
int windowHeight;

int nextBubbleDisplayX;
int nextBubbleDisplayY;
boolean isReloadingCannon;
float cannonToNextBubbleDistX;
float cannonToNextBubbleDistY;
float timeElapsedAnimation;

//Playspace elements
float timeElapsed;
Cannon cannon;
Ceiling ceiling;
Bubble nextBubble;
ArrayList<Bubble> bubbles = new ArrayList<Bubble>();

void settings()
{
    windowWidth = BUBBLE_SIZE * WIDTH_BUBBLES + PADDING * 2;
    windowHeight = BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING;
    size(windowWidth, windowHeight);
}

void setup()
{
    timeElapsed = 0;
    timeElapsedAnimation = 0;
    nextBubbleDisplayX = windowWidth / 2 - (2 * BUBBLE_SIZE);
    nextBubbleDisplayY = windowHeight - (1 * BUBBLE_SIZE);
    
    ceiling = new Ceiling(WALL_COLOR, CEILINLG_COLOR, BUBBLE_SIZE, WIDTH_BUBBLES, HEIGHT_BUBBLES, PADDING, MAX_BUBBLES);
    cannon = new Cannon(windowWidth / 2, windowHeight - (2 * BUBBLE_SIZE), BUBBLE_SIZE, CANON_COLOR);
    
    cannonToNextBubbleDistX = dist(cannon.getX(), nextBubbleDisplayX);
    cannonToNextBubbleDistY = dist(cannon.getY(), nextBubbleDisplayY);
    
    Bubble firstBubble = new Bubble(0, 0, BUBBLE_SIZE);
    bubbles.add(firstBubble);
    cannon.loadBubble(firstBubble);
    nextBubble = new Bubble(nextBubbleDisplayX, nextBubbleDisplayY, BUBBLE_SIZE);
    bubbles.add(nextBubble);
}

float dist2D(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

float dist(float x1, float x2)
{
    return abs(x2 - x1);
}

void reloadCannon(float deltaT)
{
    timeElapsedAnimation += deltaT;
    nextBubble.setX(nextBubble.getX() + cannonToNextBubbleDistX * deltaT / RELOAD_TIME);
    nextBubble.setY(nextBubble.getY() - cannonToNextBubbleDistY * deltaT / RELOAD_TIME);
    if (timeElapsedAnimation >= RELOAD_TIME)
    {
        nextBubble.setX(cannon.getX());
        nextBubble.setY(cannon.getY());
        cannon.loadBubble(nextBubble);
        isReloadingCannon = false;
        timeElapsedAnimation = 0;
        
        generateNextBubble();
    }
}

void generateNextBubble()
{
    nextBubble = new Bubble(nextBubbleDisplayX, nextBubbleDisplayY, BUBBLE_SIZE);
    bubbles.add(nextBubble);
}

void keyPressed()
{
    if (keyCode == LEFT || keyCode == 'A')
    {
        cannon.rotateLeft();
    }
    else if (keyCode == RIGHT || keyCode == 'D')
    {
        cannon.rotateRight();
    }
    else if (keyCode == ' ' || keyCode == UP || keyCode == 'W')
    {
        cannon.shoot();
        isReloadingCannon = true;
    }
}

void handleCollisions(Bubble b)
{
    if (b.getX() - BUBBLE_SIZE / 2 < PADDING) // left wall collision
    {
        b.setX(PADDING + BUBBLE_SIZE / 2);
        b.ricochet();
    }
    else if (b.getX() + BUBBLE_SIZE / 2 > windowWidth - PADDING) // right wall collision
    {
        b.setX(windowWidth - PADDING - BUBBLE_SIZE / 2);
        b.ricochet();
    }
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;
    
    if (isReloadingCannon)
    {
        reloadCannon(deltaT);
    }
    
    for (Bubble b : bubbles)
    {
        b.update();
        handleCollisions(b);
    }
    
    cannon.update(deltaT);
    ceiling.update(deltaT);
}

void draw()
{
    update();
    
    background(PLAYSPACE_COLOR);
    cannon.draw();
    drawBubbles();
    ceiling.draw();
}

void drawBubbles()
{
    for (Bubble b : bubbles)
    {
        b.draw();
    }
}