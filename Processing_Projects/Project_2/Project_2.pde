//Settings
final color BLACK = color(0, 0, 0);
final color GREY = color(126, 126, 126);
final boolean DEBUG_MODE = false;
final String LEVELS_FOLDER_NAME = "levels";
final String[] LEVELS_NAME = { "level1.lvl", "level2.lvl", "level3.lvl", "level4.lvl" };
final String FONT_NAME = "Consolas-Bold-48.vlw";

//Bubble colors
final color ORANGE = color(255, 128, 0);
final color GREEN = color(51, 255, 51);
final color RED = color(255, 51, 51);
final color BLUE = color(0, 0, 255);
final color PINK = color(230, 0, 126);
final color YELLOW = color(255, 255, 51);

final int COLOR_AMMOUNT = 6;
final color[] COLORS = { ORANGE, GREEN, RED, BLUE, PINK, YELLOW };

//Playspace Config
final int BUBBLE_SIZE = 50;
final int PADDING = 50;
final int WIDTH_BUBBLES = 10;
final int HEIGHT_BUBBLES = 17; //effective space for bubbles: HEIGHT_BUBBLES - CANNON_SPACE_BUBBLES
final int MAX_BUBBLES = 10;
final int CANNON_SPACE_BUBBLES = 2;
final float COLLISION_OFFSET_MULTIPLIER = 0.9; //not recommended to go below 0.6 (why would you?)

final int FONT_SIZE_SCORE = 50;
final int FONT_SIZE_GAMESTATE = 90;

final color WALL_COLOR = color(255, 255, 0);
final color CEILINLG_COLOR = color(100, 100, 100);
final color CANON_COLOR = color(255, 255, 0);
final color PLAYSPACE_COLOR = color(255, 255, 255);

//game variables
final float RELOAD_TIME = 0.5;
final int CLUSTER_POP_MIN = 4;
final int BUBBLE_SCORE = 25;
final int BUBBLE_SCORE_FALL = 10;

//calculation helpers
int windowWidth;
int windowHeight;

int nextBubbleDisplayX;
int nextBubbleDisplayY;
float cannonToNextBubbleDistX;
float cannonToNextBubbleDistY;

float loseConditionY;

//vars
float timeElapsed;
float timeElapsedAnimation;
boolean isReloadingCannon;

ArrayList<Bubble> removeBubblesQueue;
ArrayList<Color> uniqueColors;

int pastCeilingLevel;
int gameState; // 0 = playing, 1 = won, -1 = lost

PFont font;

//Playspace elements
Cannon cannon;
Ceiling ceiling;
Bubble nextBubble;
ArrayList<Bubble> bubbles;
BubbleGrid bubbleGrid;
int score;

void settings()
{
    windowWidth = BUBBLE_SIZE * WIDTH_BUBBLES + PADDING * 2;
    windowHeight = BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING;
    size(windowWidth, windowHeight);
}

void setup()
{
    gameState = 0;
    font = loadFont(FONT_NAME);
    bubbleGrid = new BubbleGrid(PADDING, PADDING, HEIGHT_BUBBLES - CANNON_SPACE_BUBBLES, WIDTH_BUBBLES, BUBBLE_SIZE, PADDING);
    bubbles = new ArrayList<Bubble>();
    removeBubblesQueue = new ArrayList<Bubble>();
    timeElapsed = 0;
    timeElapsedAnimation = 0;
    nextBubbleDisplayX = windowWidth / 2 - (2 * BUBBLE_SIZE);
    nextBubbleDisplayY = windowHeight - (1 * BUBBLE_SIZE);
    loseConditionY = PADDING + BUBBLE_SIZE / 2 + cos(PI / 6) * BUBBLE_SIZE * (HEIGHT_BUBBLES - CANNON_SPACE_BUBBLES - 1);
    
    ceiling = new Ceiling(WALL_COLOR, CEILINLG_COLOR, BUBBLE_SIZE, WIDTH_BUBBLES, HEIGHT_BUBBLES, PADDING, MAX_BUBBLES);
    pastCeilingLevel = ceiling.getLevel();
    cannon = new Cannon(windowWidth / 2, windowHeight - (2 * BUBBLE_SIZE), BUBBLE_SIZE, CANON_COLOR);
    
    cannonToNextBubbleDistX = abs(nextBubbleDisplayX - cannon.getX());
    cannonToNextBubbleDistY = abs(nextBubbleDisplayY - cannon.getY());
    
    loadLevel(LEVELS_NAME[0]);
}

private color randomColor()
{
    if (uniqueColors.size() > 0)
        return uniqueColors.get(int(random(uniqueColors.size()))).value;
    else
        return COLORS[int(random(COLOR_AMMOUNT))];
}

void reloadCannonAnimation(float deltaT)
{
    timeElapsedAnimation += deltaT;
    nextBubble.setX(nextBubble.getX() + cannonToNextBubbleDistX * deltaT / RELOAD_TIME);
    nextBubble.setY(nextBubble.getY() - cannonToNextBubbleDistY * deltaT / RELOAD_TIME);
    if (timeElapsedAnimation >= RELOAD_TIME)
    {
        reloadCannon();
    }
}

void reloadCannon()
{
    nextBubble.setX(cannon.getX());
    nextBubble.setY(cannon.getY());
    cannon.loadBubble(nextBubble);
    isReloadingCannon = false;
    timeElapsedAnimation = 0;
    
    generateNextBubble();
}

void generateNextBubble()
{
    uniqueColors = bubbleGrid.getUniqueColors();
    nextBubble = new Bubble(nextBubbleDisplayX, nextBubbleDisplayY, BUBBLE_SIZE, randomColor());
    bubbles.add(nextBubble);
}

void reset()
{
    ceiling.reset();
    cannon.unloadBubble();
    bubbleGrid.clear();
    bubbles.clear();
    score = 0;
    gameState = 0;
}

void loadLevel(String levelName)
{
    reset();
    
    String[] lines = loadStrings(LEVELS_FOLDER_NAME + "\\" + levelName);
    for (int i = 0; i < lines.length - 1; i++)
    {
        String tokens[] = split(lines[i], " ");
        for (int j = 0; j < tokens.length; j++)
        {
            int n = Integer.parseInt(tokens[j]);
            if (n != 0)
            {
                Bubble newBubble = new Bubble(0, 0, BUBBLE_SIZE, COLORS[n - 1]);
                bubbles.add(newBubble);
                bubbleGrid.placeBubble(i, j, newBubble);
            }
        }
    }
    
    generateNextBubble();
    reloadCannon();
}

void keyPressed()
{    
    if (gameState == 0)
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
            if (cannon.shoot())
            {
                isReloadingCannon = true;
            }
        }
    }
    
    if (keyCode == '1' || keyCode == '2' || keyCode == '3' || keyCode == '4')
    {
        loadLevel(LEVELS_NAME[Integer.parseInt(str(char(keyCode))) - 1]);
    }
}

void mousePressed()
{
    if (DEBUG_MODE && gameState == 0)
    {
        if (mouseButton == LEFT)
        {
            Bubble b = cannon.unloadBubble();
            b.setPos(mouseX, mouseY);
            bubbleGrid.snap(b);
            handleClusterFromCell(b.getCell());
            reloadCannon();
        }
        else if (mouseButton == RIGHT)
        {
            Bubble b = cannon.unloadBubble();
            bubbles.remove(b);
            reloadCannon();
        }
    }
    
}

void generateScoreFromCluster(int size)
{
    int singleScore = BUBBLE_SCORE * (int)pow(2, size - CLUSTER_POP_MIN);
    score += size * singleScore;
}

void generateScoreFromFalling(int size)
{
    int singleScore = BUBBLE_SCORE_FALL * (int)pow(2, size - 1);
    score += size * singleScore;
}

void win()
{
    println("win condition triggered.");
    gameState = 1;
}

void lose()
{
    println("lose condition triggered.");
    gameState = -1;
}

void checkWinCondition()
{
    if (bubbleGrid.isEmpty())
        win();
}

void checkLoseCondition()
{
    if (bubbleGrid.furthestPointY() >= loseConditionY)
        lose();
}

void handleClusterFromCell(BubbleCell cell)
{
    ArrayList<BubbleCell> colorCluster = bubbleGrid.getColorCluster(cell);
    if (colorCluster.size() >= CLUSTER_POP_MIN)
    {
        println("Cluster detected!");
        for (BubbleCell c : colorCluster)
        {
            removeBubblesQueue.add(c.getBubble());
            c.removeBubble();
        }
        int bubblesFreed = bubbleGrid.freeUnconnectedBubbles();
        generateScoreFromCluster(colorCluster.size());
        generateScoreFromFalling(bubblesFreed);
        checkWinCondition();
    }
}

void handleCollisions(Bubble b)
{
    if (b.isBelowScreen(windowHeight))
    {
        println("Bubble out of screen cleaned up!");
        removeBubblesQueue.add(b);
    }
    
    if (b.hasCollision())
    {
        b.handleWallCollision(PADDING, windowWidth); // wall collision
        
        if (b.collidesCeiling(ceiling.getHeight())) // ceiling collision
        {
            println("ceiling collision detected!");
            b.stop();
            b.setCollision(false);
            bubbleGrid.snapCeiling(b);
            checkLoseCondition();
        }
        
        for (Bubble bubble : bubbles) //bubble collision
        {
            if (b != bubble && b.collides(bubble, COLLISION_OFFSET_MULTIPLIER))
            {
                println("collision detected!");
                b.stop();
                b.setCollision(false);
                bubbleGrid.snap(b, bubble);
                checkLoseCondition();
                handleClusterFromCell(b.getCell());
            }
        }
    }
}

void clearRemoveBubblesQueue()
{
    for (Bubble b : removeBubblesQueue)
        bubbles.remove(b);
}

void updateBubbles(float deltaT)
{
    for (Bubble b : bubbles)
    {
        b.update(deltaT);
        handleCollisions(b);
    }
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;
    
    updateBubbles(deltaT);
    
    if (isReloadingCannon)
        reloadCannonAnimation(deltaT);
    
    clearRemoveBubblesQueue();
    if (gameState == 0)
    {   
        if (pastCeilingLevel != ceiling.getLevel())
        {
            pastCeilingLevel = ceiling.getLevel();
            checkLoseCondition();
        }
        
        cannon.update(deltaT);
        ceiling.update(deltaT);
        bubbleGrid.update(ceiling.getLevel(), ceiling.getHeight());
    }
}

void drawBubbles()
{
    for (Bubble b : bubbles)
        b.draw();
}

void drawScore()
{
    textFont(font);
    fill(BLACK);
    textSize(FONT_SIZE_SCORE);
    textAlign(CENTER, CENTER);
    text("SCORE: " + str(score), windowWidth / 2, PADDING / 2);
}

void drawLoseCondition()
{
    stroke(BLACK);
    strokeWeight(4);
    line(PADDING, loseConditionY, windowWidth - PADDING, loseConditionY);
}

void drawGameStateScreen()
{
    clearRemoveBubblesQueue();
    
    fill(GREY);
    rectMode(CENTER);
    rect(windowWidth / 2, windowHeight / 2,(windowWidth / 10) * 9, windowHeight / 4);
    String gamestateText = "Error";
    textFont(font);
    if (gameState == 1)
    {
        gamestateText = "Victory!";
        fill(GREEN);
    }
    else if (gameState == -1)
    {
        gamestateText = "Game Over!";
        fill(RED);
    }
    
    textSize(FONT_SIZE_GAMESTATE);
    textAlign(CENTER, CENTER);
    text(gamestateText, windowWidth / 2, windowHeight / 2);
}

void draw()
{
    update();
    
    background(PLAYSPACE_COLOR);
    if (DEBUG_MODE)
        bubbleGrid.drawDebug();
    cannon.draw();
    drawBubbles();
    drawLoseCondition();
    ceiling.draw();
    drawScore();
    if (gameState != 0) // win / lose
        drawGameStateScreen();
}