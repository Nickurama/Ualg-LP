class Ceiling
{
    final private float COOLDOWN = 20;
    
    private color topColor;
    private color descendingColor;
    private int bubbleSize;
    private int widthBubbles;
    private int heightBubbles;
    private int padding;
    private int maxLevel;
    
    private int level;
    private float timeElapsed;
    
    public Ceiling(color topColor, color descendingColor, int bubbleSize, int widthBubbles, int heightBubbles, int padding, int maxLevel)
    {
        this.topColor = topColor;
        this.descendingColor = descendingColor;
        this.bubbleSize = bubbleSize;
        
        this.widthBubbles = widthBubbles;
        this.heightBubbles = heightBubbles;
        this.padding = padding;
        this.maxLevel = maxLevel;
        
        this.level = 0;
        this.timeElapsed = 0;
    }
    
    public void update(float deltaT)
    {
        timeElapsed += deltaT;
        if (timeElapsed >= COOLDOWN)
        {
            timeElapsed -= COOLDOWN;
            if (level < maxLevel)
            {
                level++;
            }
        }
    }
    
    public void reset()
    {
        this.level = 0;
        this.timeElapsed = 0;
    }
    
    public void draw()
    {
        rectMode(CORNER);
        noStroke();
        fill(topColor);
        rect(0, 0, bubbleSize * widthBubbles + 2 * padding, padding); //top section
        rect(0, 0, padding, bubbleSize * heightBubbles + padding); //left side
        rect(bubbleSize * widthBubbles + padding, 0, padding, bubbleSize * heightBubbles + padding); //right side
        fill(descendingColor);
        rect(padding, padding, bubbleSize * widthBubbles, bubbleSize * level * cos(PI / 6));
    }
    
    public float getHeight() { return this.padding + this.level * this.bubbleSize * cos(PI / 6); }
    public int getLevel() { return this.level; }
}