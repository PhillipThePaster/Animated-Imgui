// This will be in your main drawing function for imgui, either gui or main, wherever ImGui::Begin is
// это будет в вашей основной функции рисования для imgui, либо gui, либо main, где бы ни находился ImGui::Begin


//Variables || Переменные

static float animationTime = 0.0f;
static float animationSpeed = 1.0f;
enum AnimationDirection { LEFT, RIGHT };
static AnimationDirection animationDirection = RIGHT;




// Menu Function || Функция меню
            if (ImGui::BeginCombo("Rgb Animation Direction", (animationDirection == LEFT) ? "Left" : "Right")) { // Направление анимации Rgb
                if (ImGui::Selectable("Left", animationDirection == LEFT)) {
                    animationDirection = LEFT;
                }
                if (ImGui::Selectable("Right", animationDirection == RIGHT)) {
                    animationDirection = RIGHT;
                }
                ImGui::EndCombo();
            }



// Drawing Function || Функция рисования
        ImGuiIO& io = ImGui::GetIO();
        float deltaTime = io.DeltaTime;

        animationTime += deltaTime * animationSpeed * (animationDirection == LEFT ? 1 : -1);

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 gradientStart = { ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y + ImGui::GetContentRegionAvail().y - ImGui::GetTextLineHeight() };
        ImVec2 gradientEnd = { gradientStart.x + ImGui::GetContentRegionAvail().x, gradientStart.y + ImGui::GetTextLineHeight() };
        float stepSize = (gradientEnd.x - gradientStart.x) / ImGui::GetContentRegionAvail().x;

        for (float x = gradientStart.x; x < gradientEnd.x; x += stepSize) {
            float t = (x - gradientStart.x) / (gradientEnd.x - gradientStart.x);
            float r = 255.0f * (sinf(animationTime + t * 3.0f) * 0.5f + 0.5f);
            float g = 255.0f * (sinf(animationTime + t * 3.0f + 2.0f) * 0.5f + 0.5f);
            float b = 255.0f * (sinf(animationTime + t * 3.0f + 4.0f) * 0.5f + 0.5f);
            ImU32 color = IM_COL32((int)r, (int)g, (int)b, 255);
            drawList->AddRectFilled(ImVec2(x, gradientStart.y), ImVec2(x + stepSize, gradientEnd.y), color);
        }

        drawList->AddRect(gradientStart, gradientEnd, IM_COL32(0, 0, 0, 255));

