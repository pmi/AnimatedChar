
enum AnimationStatus { STARTED, PROGRESS, STOPPED };

class AnimationListener {
   public:
    virtual void onAnimation( AnimationStatus status, char from, char to, byte progress ) = 0;
};