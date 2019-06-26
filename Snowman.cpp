//
// Created by Krzysztof Sychla on 2019-06-22.
//

#include "Snowman.h"

inline static glm::vec3 toVec3(glm::vec4 a){
    return glm::vec3(a.x, a.y, a.z);
}

Snowman::Snowman(generateHeight* h, Camera* cam, glm::vec2 position) {
    pos = glm::vec3(position.x,h->height(position.x,position.y)-17,position.y);
    camera = cam;
    height = h;
}

void Snowman::move(GLFWwindow *window, double timePassed, Pocisk &pocisk, bool flaga)
{
    isThirdPerson = flaga;
    glm::vec3 dir = glm::vec3(0);
    float rotate_up = 0;
    rotate_left = 0;
    float rotationSpeed = 1.f * (float)timePassed;
    glm::mat4 rotate;
    if(isThirdPerson){
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) dir += front*5.f ;
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed ;
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) dir += -front*5.f ;
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left += -rotationSpeed ;
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotate_up -= rotationSpeed;
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotate_up += rotationSpeed;



        rotation += rotate_left;
        rotate = glm::mat4(1);
        rotate = glm::rotate(rotate, rotate_left, up );
//    rotate = glm::rotate(rotate, rotate_up * timePassed, left );
        applyRotation(rotate);
        pos+= dir * (float)timePassed;
        pos = glm::vec3(pos.x, height->height(pos.x, pos.z)-17, pos.z);
        //printf("%f %f %f\n", pos.x, pos.y, pos.z);

        frontFirstPerson = front;
        upFirstPerson = up;
    }else{
        rotate_up = 0.f;
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotate_up += -rotationSpeed;
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed;
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotate_up += rotationSpeed;
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left += -rotationSpeed;
//        pocisk = new Pocisk();
        if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS  && !flagaEnter){
            pocisk.enter_press();
            flagaEnter = true;
        }
//        printf("%d", isThirdPerson);

        left = glm::cross(up, front);
        rotate = glm::mat4(1);
        rotate = glm::rotate(rotate, rotate_left, up );
        applyRotation(rotate);
        rotate = glm::rotate(rotate, rotate_up, left );
        frontFirstPerson = toVec3(rotate * glm::vec4(frontFirstPerson, 1));
        upFirstPerson    = toVec3(rotate * glm::vec4(upFirstPerson   , 1));

        rotate_left += rotation;
        if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE && flagaEnter){
            pocisk.enter_release();
            flagaEnter = false;
            pocisk.strzal(pos, frontFirstPerson/sqrt(frontFirstPerson.x*frontFirstPerson.x + frontFirstPerson.y*frontFirstPerson.y + frontFirstPerson.z* frontFirstPerson.z));
        }
//        frontFirstPerson = glm::normalize(frontFirstPerson);

        rotation = rotate_left;
//        front = glm::vec3(frontFirstPerson.x, front.y, frontFirstPerson.z);
            //pocisk.strzal(pos, glm::vec2(-rotation, 0.0f)) ;
//        printf("%f\n", rotation);
        //printf("%f %f %f\n", pos.x, pos.y, pos.z);
//        delete pocisk;
    }
}

void Snowman::applyRotation(glm::mat4 rotation) {
//    pos   = toVec3(rotation * glm::vec4(pos  ,1));
    front = toVec3(rotation * glm::vec4(front,1));
//    up    = toVec3(rotation * glm::vec4(up   ,1));
//    left  = toVec3(rotation * glm::vec4(left ,1));
}

glm::mat4 Snowman::getView()
{
    if(isThirdPerson){
        return glm::lookAt( pos - 18.f * front + 10.f * up,
                            pos + 18.f * front,
                            up);
    } else {
        return glm::lookAt( pos + 5.f * front + 10.f * up,
                            pos + 18.f * frontFirstPerson + 10.f * up,
                            upFirstPerson);

    }
}

glm::mat4 Snowman::getModel()
{
    glm::mat4 M = glm::mat4(1);
    M = glm::translate(M, pos);
    M = glm::rotate(M, rotation, up);
    return M;
}
