#ifndef SEGMENT_DISPLAY_H_INC
#define SEGMENT_DISPLAY_H_INC

class SegmentDisplay {

  public:
    SegmentDisplay(int (&paramPins)[7], bool paramShowZero);
    void setValue(int value);

  private:
    static bool NUMBERS[10][7];
    
    int pins[7];
    bool showZero;
  
};

#endif

