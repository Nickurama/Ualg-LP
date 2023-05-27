//this class represents a boxying type for the primitive type color, so that we can use it in ArrayLists
class Color
{
    public color value;
    
    Color(color c)
    {
        this.value = c;
    }
    
    //overriding equals method
    @Override
    boolean equals(Object o)
    {
        if (o == this) return true;
        
        if (!(o instanceof Color)) return false;
        
        Color c = (Color) o;
        
        return this.value == c.value;
    }
}