class Ceiling
{
    final private float COOLDOWN = 20;
    
    private color topColor;
    private color descendingColor;
    private int bubbleSize;
    private int widthBubbles;
    private int padding;
    private int maxLevel;
    
    private int level;
    private float timeElapsed;
    
    public Ceiling(color topColor, color descendingColor, int bubbleSize, int widthBubbles, int padding, int maxLevel)
    {
        this.topColor = topColor;
        this.descendingColor = descendingColor;
        this.bubbleSize = bubbleSize;
        
        this.widthBubbles = widthBubbles;
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
    
    public void draw()
    {
        rectMode(CORNER);
        noStroke();
        fill(topColor);
        rect(padding, 0, bubbleSize * widthBubbles, padding);
        fill(descendingColor);
        rect(padding, padding, bubbleSize * widthBubbles, bubbleSize * level);
    }
}