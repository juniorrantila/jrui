#include <UI/Controller.h>
#include <UI/Window.h>

struct MainController : UI::Controller {
    UI::ViewRef body() override {
        return VStack(
            Text("Hello, World!")
        )
        .alignment(center)
        .sizing(fillArea);
    }
};

int main()
{
    auto controller = MainController();
    auto window = UI::Window()
        .controller(controller)
        .min_size(900, 600);
    window.run();
}
