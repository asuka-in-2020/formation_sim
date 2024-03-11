class Vector2 {
    private:
        float x_;
        float y_;

    public:
        inline Vector2(){
            x_=0.0f;
            y_=0.0f;
        }
        inline Vector2(float x, float y): x_(x), y_(y){

        }
        inline Vector2 operator+(const Vector2& vec){
            return Vector2(x_ + vec.x_, y_ + vec.y_);
        }
};