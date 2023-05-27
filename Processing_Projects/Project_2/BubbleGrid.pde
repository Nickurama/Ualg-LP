class BubbleGrid
{
    private float x;
    private float y;
    private int rows;
    private int columns;
    private int bubbleSize;
    private int padding;
    private int halfBubbleSize;
    private float cosThirty;
    private BubbleCell bubbleGrid[][];
    private int currentCeilingLevel;
    
    public BubbleGrid(float x, float y, int rows, int columns, int bubbleSize, int padding)
    {
        this.x = x;
        this.y = y;
        this.rows = rows;
        this.columns = columns;
        this.bubbleSize = bubbleSize;
        this.padding = padding;
        this.halfBubbleSize = bubbleSize / 2;
        this.cosThirty = cos(PI / 6);
        this.bubbleGrid = new BubbleCell[rows][columns];
        this.currentCeilingLevel = 0;
        
        for (int i = 0; i < rows; i++)
        {
            bubbleGrid[i] = generateLine(i);
        }
    }
    
    private BubbleCell[] generateLine(int line)
    {
        BubbleCell bubbleLine[] = new BubbleCell[columns];
        
        float cellY = line * bubbleSize * cosThirty + halfBubbleSize + padding;
        
        if (line % 2 == 0)
        {
            for (int i = 0; i < columns; i++)
            {
                float cellX = i * bubbleSize + halfBubbleSize + padding;
                bubbleLine[i] = new BubbleCell(cellX, cellY, line, i);
            }
        }
        else
        {
            for (int i = 0; i < columns; i++)
            {
                float cellX = (i + 1) * bubbleSize + padding;
                bubbleLine[i] = new BubbleCell(cellX, cellY, line, i + 1);
            }
        }
        return bubbleLine;
    }
    
    public void snapCeiling(Bubble b)
    {
        float closestDist = b.dist(bubbleGrid[0][0].getX(), bubbleGrid[0][0].getY());
        BubbleCell closestCell = bubbleGrid[0][0]; //default
        
        for (BubbleCell cell : bubbleGrid[0]) //closest cell
        {
            float newDist = b.dist(cell);
            if (newDist < closestDist && !cell.hasBubble())
            {
                closestDist = newDist;
                closestCell = cell;
            }
        }
        
        closestCell.setBubble(b);
        b.setCell(closestCell);
    }
    
    private ArrayList<BubbleCell> getAdjacentCells(BubbleCell c)
    {
        ArrayList<BubbleCell> adjacentCells = new ArrayList<BubbleCell>();
        int row = c.getRow();
        int column = c.getColumn();
        
        if (row % 2 == 0) // even
        {
            if (column - 1 >= 0) // left
                adjacentCells.add(bubbleGrid[row][column - 1]);
            if (column + 1 < columns) //right
                adjacentCells.add(bubbleGrid[row][column + 1]);
            
            if (row - 1 > 0) // up
            {
                int columnIndex = column - 1; // odds are shifted 1 to the left in the array in relation to column index
                if (column > 0) // left (same column)
                    adjacentCells.add(bubbleGrid[row - 1][columnIndex]);
                if (column < 9) // right
                    adjacentCells.add(bubbleGrid[row - 1][columnIndex + 1]);
            }
            
            if (row + 1 < rows) // down
            {
                int columnIndex = column - 1; // odds are shifted 1 to the left in the array
                if (column > 0) // left (same column)
                    adjacentCells.add(bubbleGrid[row + 1][columnIndex]);
                if (column < 9) // right
                    adjacentCells.add(bubbleGrid[row + 1][columnIndex + 1]);
            }
        }
        else // odd
        {
            int columnIndex = column - 1; // odds are shifted 1 to the left in the array
            if (column - 1 > 0) // left
                adjacentCells.add(bubbleGrid[row][columnIndex - 1]);
            if (column + 1 < columns) //right
                adjacentCells.add(bubbleGrid[row][columnIndex + 1]);
            
            if (row - 1 >= 0) // up
            {
                adjacentCells.add(bubbleGrid[row - 1][column - 1]); // left
                adjacentCells.add(bubbleGrid[row - 1][column]); // right
            }
            
            if (row + 1 <= rows) // down
            {
                adjacentCells.add(bubbleGrid[row + 1][column - 1]); // left
                adjacentCells.add(bubbleGrid[row + 1][column]); // right
            }
        }
        
        return adjacentCells;
    }
    
    public void snap(Bubble snapBubble, Bubble anchor)
    {
        ArrayList<BubbleCell> adjacentCells = getAdjacentCells(anchor.getCell());
        ArrayList<BubbleCell> freeCells = new ArrayList<BubbleCell>();
        for (BubbleCell cell : adjacentCells)
            if (!cell.hasBubble())
                freeCells.add(cell);
        
        if (freeCells.size() > 0)
        {
            float closestDist = snapBubble.dist(freeCells.get(0));
            BubbleCell closestCell = freeCells.get(0);
            
            for (BubbleCell cell : freeCells)
            {
                float newDist = snapBubble.dist(cell);
                if (newDist < closestDist)
                {
                    closestDist = newDist;
                    closestCell = cell;
                }
            }
            
            closestCell.setBubble(snapBubble);
            snapBubble.setCell(closestCell);
        }
        else
        {
            println("Error: no available adjacent cell!");
        }
    }
    
    private float dist(float x1, float y1, float x2, float y2)
    {
        return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    }
    
    public void snap(Bubble snapBubble)
    {
        float closestDist = snapBubble.dist(bubbleGrid[0][0]);
        BubbleCell closestCell = bubbleGrid[0][0];
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell c : row)
            {
                float dist = snapBubble.dist(c);
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestCell = c;
                }
            }
        }
        
        closestCell.setBubble(snapBubble);
        snapBubble.setCell(closestCell);
    }
    
    private ArrayList<BubbleCell> getColorCluster(BubbleCell initial)
    {
        ArrayList<BubbleCell> closed = new ArrayList<BubbleCell>();
        ArrayList<BubbleCell> open = new ArrayList<BubbleCell>();
        open.add(initial);
        
        while(open.size() > 0)
        {
            BubbleCell cell = open.get(0);
            open.remove(0);
            closed.add(cell);
            
            ArrayList<BubbleCell> adjacentCells = getAdjacentCells(cell);
            for (BubbleCell c : adjacentCells)
                if (c.hasBubble() && c.getBubble().getColor() == cell.getBubble().getColor() && !closed.contains(c) && !open.contains(c))
                    open.add(c);
        }
        
        return closed;
    }
    
    private void markConnectedCells()
    {
        ArrayList<BubbleCell> open = new ArrayList<BubbleCell>();
        for (BubbleCell c : this.bubbleGrid[0])
        {
            if (c.hasBubble())
            {
                open.add(c);
            }
        }
        
        while(open.size() > 0)
        {
            BubbleCell c = open.get(0);
            open.remove(0);
            c.setConnected();
            ArrayList<BubbleCell> adjacentCells = getAdjacentCells(c);
            for (BubbleCell adjacentCell : adjacentCells)
            {
                if (adjacentCell.hasBubble() && !adjacentCell.isConnected() && !open.contains(adjacentCell))
                {
                    open.add(adjacentCell);
                }
            }
        }
    }
    
    public void freeUnconnectedBubbles()
    {
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell cell : row)
            {
                cell.setDisconnected();
            }
        }
        
        markConnectedCells();
        
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell cell : row)
            {
                if (cell.hasBubble && !cell.isConnected())
                {
                    cell.getBubble().launch(PI / 2);
                    cell.getBubble().setCollision(false);
                    cell.removeBubble();
                }
            }
        }
    }
    
    public void placeBubble(int row, int column, Bubble bubble)
    {
        if (row % 2 != 0)
        {
            column -= 1;
        }
        if (row >= 0 && row <= this.rows && column >= 0 && column <= this.columns)
        {
            bubbleGrid[row][column].setBubble(bubble);
            bubble.setCell(bubbleGrid[row][column]);
        }
    }
    
    public void clear()
    {
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell cell : row)
            {
                cell.removeBubble();
            }
        }
    }
    
    public ArrayList<Color> getUniqueColors()
    {
        ArrayList<Color> uniqueColors = new ArrayList<Color>();
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell cell : row)
            {
                if (cell.hasBubble())
                {
                    Color c = new Color(cell.getBubble().getColor());
                    if (!uniqueColors.contains(c))
                    {
                        uniqueColors.add(c);
                    }
                }
            }
        }
        println(uniqueColors.size());
        return uniqueColors;
    }
    
    private void updateCells(float yOffset)
    {
        for (BubbleCell[] row : bubbleGrid)
        {
            for (BubbleCell cell : row)
            {
                cell.setY(cell.getY() + yOffset);
            }
        }
    }
    
    public void update(int ceilingLevel, float ceilingHeight)
    {
        if (ceilingLevel != currentCeilingLevel)
        {
            this.currentCeilingLevel = ceilingLevel;
            float yOffset = ceilingHeight - this.y;
            updateCells(yOffset);
            this.y = ceilingHeight;
        }
    }
    
    private void drawDebug()
    {
        for (int i = 0; i < rows; i++)
        {
            int effectiveColumns = columns;
            if (i % 2 == 1)
            {
                effectiveColumns -= 1;
            }
            for (int j = 0; j < effectiveColumns; j++)
            {
                bubbleGrid[i][j].debugDraw();
            }
        }
    }
}