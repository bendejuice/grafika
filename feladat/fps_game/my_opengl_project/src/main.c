#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // For rand()
#include <math.h> // For sqrtf and fabsf

#include "shader.h"
#include "model.h"
#include "texture.h"
#include "camera.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define NUM_CUBES 20

// Global variables for light intensity and help screen
float lightIntensity = 1.0f;
bool showHelp = false;

// Cube positions and active status
vec3 cubePositions[NUM_CUBES];
bool cubeActive[NUM_CUBES];

// Hand animation variables
float handAnimationTime = 0.0f;
float handAnimationSpeed = 5.0f; // Speed of hand idle bobbing
float handMaxIdleOffset = 0.05f; // Max vertical offset for hand idle animation

// Pickup animation variables
bool isPickingUp = false;
float handPickupProgress = 0.0f; // 0.0 to 1.0
float pickupAnimationDuration = 0.2f; // Duration of the pickup animation in seconds
float pickupMaxForwardOffset = 0.5f; // Max forward offset during pickup animation

// Function to draw text (simplified, requires external library or more complex implementation)
// For demonstration, we'll just print to console or use a very basic OpenGL text rendering if available.
void renderHelpScreen(int screenWidth, int screenHeight) {
// This is a placeholder. For actual in-game text rendering, you'd typically use:
// - SDL_ttf (requires linking SDL2_ttf)
// - FreeType library
// - Simple bitmap font rendering using quads and textures
// Since adding a full text rendering system is beyond the scope of this request,
// we'll just use a simple white rectangle to indicate a help screen,
// and ideally, you'd integrate a proper text rendering solution here.

// A very basic way to draw a transparent overlay:
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_DEPTH_TEST);

glUseProgram(0); // Use fixed function or a simple untextured shader
glColor4f(0.0f, 0.0f, 0.0f, 0.7f); // Black, semi-transparent background

glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
glOrtho(0, screenWidth, 0, screenHeight, -1, 1); // Orthographic projection

glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();

// Draw a rectangle for the help screen background
glBegin(GL_QUADS);
glVertex2f(screenWidth * 0.1f, screenHeight * 0.1f);
glVertex2f(screenWidth * 0.9f, screenHeight * 0.1f);
glVertex2f(screenWidth * 0.9f, screenHeight * 0.9f);
glVertex2f(screenWidth * 0.1f, screenHeight * 0.9f);
glEnd();

// Reset to previous state
glPopMatrix();
glMatrixMode(GL_PROJECTION);
glPopMatrix();

glEnable(GL_DEPTH_TEST);
glDisable(GL_BLEND);

// In a real scenario, you'd render text here:
printf("--- Segítség ---\n");
printf("W, A, S, D: Mozgás\n");
printf("Egér: Kamera forgatása\n");
printf("Bal Shift: Gyorsabb mozgás\n");
printf("+/-: Fényerő állítása\n");
printf("E: Kocka felvétele (ha ránézel és közel vagy)\n");
printf("F1: Segítség ki/be\n");
printf("ESC: Kilépés\n");
printf("----------------\n");
}


int main(int argc, char *argv[]) {
if (SDL_Init(SDL_INIT_VIDEO) < 0) {
fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
return -1;
}

SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

SDL_Window* window = SDL_CreateWindow("Számítógépes Grafika Beadandó",
SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
WINDOW_WIDTH, WINDOW_HEIGHT,
SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
if (!window) {
fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
SDL_Quit();
return -1;
}

SDL_GLContext glContext = SDL_GL_CreateContext(window);
if (!glContext) {
fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
SDL_DestroyWindow(window);
SDL_Quit();
return -1;
}

glewExperimental = GL_TRUE;
if (glewInit() != GLEW_OK) {
fprintf(stderr, "Failed to initialize GLEW\n");
SDL_GL_DeleteContext(glContext);
SDL_DestroyWindow(window);
SDL_Quit();
return -1;
}

glEnable(GL_DEPTH_TEST);

GLuint shaderProgram = loadShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
if (!shaderProgram) {
fprintf(stderr, "Failed to load shaders\n");
SDL_GL_DeleteContext(glContext);
SDL_DestroyWindow(window);
SDL_Quit();
return -1;
}

// Load Models
Model grassModel; // For the ground plane
if (!loadOBJ("assets/models/grass_plane.obj", &grassModel)) {
fprintf(stderr, "Failed to load grass_plane model\n");
return -1;
}
grassModel.textureID = loadTexture("assets/textures/grass_texture.png");
if (!grassModel.textureID) {
fprintf(stderr, "Failed to load grass texture\n");
return -1;
}

Model cubeModel;
if (!loadOBJ("assets/models/cube.obj", &cubeModel)) {
fprintf(stderr, "Failed to load cube model\n");
return -1;
}
cubeModel.textureID = loadTexture("assets/textures/cube_texture.png");
if (!cubeModel.textureID) {
fprintf(stderr, "Failed to load cube texture\n");
return -1;
}

Model handModel;
if (!loadOBJ("assets/models/hand.obj", &handModel)) {
fprintf(stderr, "Failed to load hand model\n");
return -1;
}
handModel.textureID = loadTexture("assets/textures/hand_texture.png");
if (!handModel.textureID) {
fprintf(stderr, "Failed to load hand texture\n");
return -1;
}

Model characterModel; // Placeholder for character model
if (!loadOBJ("assets/models/character.obj", &characterModel)) { // You'll need to create this OBJ
fprintf(stderr, "Failed to load character model\n");
return -1;
}
characterModel.textureID = loadTexture("assets/textures/character_texture.png");
if (!characterModel.textureID) {
fprintf(stderr, "Failed to load character texture\n");
return -1;
}

Model mountainModel;
if (!loadOBJ("assets/models/mountain.obj", &mountainModel)) {
fprintf(stderr, "Failed to load mountain model\n");
return -1;
}
mountainModel.textureID = loadTexture("assets/textures/mountain_texture.png");
if (!mountainModel.textureID) {
fprintf(stderr, "Failed to load mountain texture\n");
return -1;
}

// Initialize Camera
Camera camera;
vec3 camPos = {0.0f, 1.0f, 5.0f}; // Position above the ground
vec3 worldUp = {0.0f, 1.0f, 0.0f};
initCamera(&camera, camPos, worldUp, -90.0f, 0.0f);

// Initialize cube positions randomly
srand(SDL_GetTicks()); // Seed random number generator
for (int i = 0; i < NUM_CUBES; ++i) {
cubePositions[i][0] = (float)(rand() % 200 - 100) / 10.0f; // -10.0 to 10.0
cubePositions[i][1] = 0.5f; // Slightly above the ground
cubePositions[i][2] = (float)(rand() % 200 - 100) / 10.0f;
cubeActive[i] = true;
}

bool running = true;
SDL_Event event;

float lastTime = SDL_GetTicks() / 1000.0f;
float deltaTime;

SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse to window

while (running) {
float currentTime = SDL_GetTicks() / 1000.0f;
deltaTime = currentTime - lastTime;
lastTime = currentTime;

// Update hand idle animation time
handAnimationTime += deltaTime * handAnimationSpeed;

// Update pickup animation progress
if (isPickingUp) {
handPickupProgress += deltaTime / pickupAnimationDuration;
if (handPickupProgress >= 1.0f) {
handPickupProgress = 1.0f;
isPickingUp = false;
}
}

while (SDL_PollEvent(&event)) {
if (event.type == SDL_QUIT)
running = false;
else if (event.type == SDL_KEYDOWN) {
if (event.key.keysym.sym == SDLK_ESCAPE)
running = false;
if (event.key.keysym.sym == SDLK_F1)
showHelp = !showHelp; // Toggle help screen
if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS) {
lightIntensity += 0.1f;
if (lightIntensity > 2.0f) lightIntensity = 2.0f;
}
if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS) {
lightIntensity -= 0.1f;
if (lightIntensity < 0.1f) lightIntensity = 0.1f;
}
if (event.key.keysym.sym == SDLK_e) {
if (!isPickingUp) { // Only allow pickup if not already picking up
vec3 rayOrigin;
glm_vec3_copy(camera.position, rayOrigin);
vec3 rayDirection;
glm_vec3_copy(camera.front, rayDirection);

float maxPickupDistance = 5.0f; // Max distance to pick up a cube
float minDotProduct = 0.95f; // How directly we need to look at it (cosine of angle)

for (int i = 0; i < NUM_CUBES; ++i) {
if (cubeActive[i]) {
vec3 dirToCube;
glm_vec3_sub(cubePositions[i], rayOrigin, dirToCube);
// Calculate length using sqrtf and dot product for compatibility
float distToCube = sqrtf(glm_vec3_dot(dirToCube, dirToCube));

if (distToCube < maxPickupDistance) {
glm_vec3_normalize(dirToCube);
float dotProduct = glm_vec3_dot(rayDirection, dirToCube);

// Check if looking directly enough at the cube and within Y-height range
// Assuming cubes are at y=0.5f and camera at y=1.0f
float cubeYCenter = cubePositions[i][1];
float cameraY = camera.position[1];
float yDiff = fabsf(cubeYCenter - cameraY); // Difference in Y height

if (dotProduct > minDotProduct && yDiff < 1.0f) { // Adjust Y-diff tolerance as needed
printf("Picked up cube %d!\n", i);
cubeActive[i] = false; // "Remove" the cube
isPickingUp = true;
handPickupProgress = 0.0f;
break; // Pick up only one cube at a time
}
}
}
}
}
}
} else if (event.type == SDL_MOUSEMOTION) {
processMouseMovement(&camera, (float)event.motion.xrel, (float)-event.motion.yrel);
}
}

const Uint8* state = SDL_GetKeyboardState(NULL);
float currentSpeed = camera.movementSpeed;
if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) {
camera.movementSpeed *= 2.0f; // Sprint
}

if (state[SDL_SCANCODE_W]) processKeyboard(&camera, CAMERA_FORWARD, deltaTime);
if (state[SDL_SCANCODE_S]) processKeyboard(&camera, CAMERA_BACKWARD, deltaTime);
if (state[SDL_SCANCODE_A]) processKeyboard(&camera, CAMERA_LEFT, deltaTime);
if (state[SDL_SCANCODE_D]) processKeyboard(&camera, CAMERA_RIGHT, deltaTime);

camera.movementSpeed = currentSpeed; // Reset speed

glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Sky color
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glUseProgram(shaderProgram);

// Matrices
mat4 projection, view, model;
glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 200.0f, projection);
glm_lookat(camera.position, (vec3){camera.position[0] + camera.front[0], camera.position[1] + camera.front[1], camera.position[2] + camera.front[2]}, camera.up, view);

GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)projection);

GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");

glUniform3f(lightPosLoc, 10.0f, 20.0f, 10.0f); // Light source position
glUniform3f(viewPosLoc, camera.position[0], camera.position[1], camera.position[2]);
glUniform3f(lightColorLoc, lightIntensity, lightIntensity, lightIntensity); // Adjust light color based on intensity

// Draw Grass Plane
glm_mat4_identity(model);
glm_translate(model, (vec3){0.0f, -0.1f, 0.0f}); // Slightly below character
glm_scale(model, (vec3){100.0f, 1.0f, 100.0f}); // Large plane
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, grassModel.textureID);
drawModel(&grassModel);

// Draw Mountains
// Place multiple mountains around the scene
for (int i = 0; i < 8; ++i) { // Example: 8 mountains
glm_mat4_identity(model);
float angle = glm_rad(i * 45.0f);
glm_translate(model, (vec3){cos(angle) * 70.0f, -10.0f, sin(angle) * 70.0f}); // Far away and lower
glm_scale(model, (vec3){50.0f, 50.0f, 50.0f}); // Make mountains large
glm_rotate(model, glm_rad(i * 90.0f), (vec3){0.0f, 1.0f, 0.0f}); // Rotate them
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, mountainModel.textureID);
drawModel(&mountainModel);
}

// Draw Character (at camera position, adjusted for character height)
glm_mat4_identity(model);
// Position character slightly behind and below camera to simulate first-person view
vec3 charPos;
glm_vec3_copy(camera.position, charPos);
charPos[1] -= 0.8f; // Adjust for character height
glm_vec3_sub(charPos, camera.front, charPos); // Slightly behind camera
glm_translate(model, charPos);
glm_rotate(model, glm_rad(-camera.yaw + 90.0f), (vec3){0.0f, 1.0f, 0.0f}); // Rotate character with camera yaw
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, characterModel.textureID);
drawModel(&characterModel);

// Draw Hand (attached to character, animated)
glm_mat4_identity(model);
vec3 handPos;
// Kezdjük a kéz pozícióját a kamera pozíciójából
glm_vec3_copy(camera.position, handPos);
vec3 temp_vec;

// Offset a kamera "jobb" irányába
// Ezen értékkel lehet finomhangolni a kéz vízszintes pozícióját a képernyőn.
// Növeld az értéket, ha jobbra akarod vinni.
glm_vec3_scale(camera.right, 0.5f, temp_vec); // Enyhén jobbra
glm_vec3_add(handPos, temp_vec, handPos);

// Offset a kamera "le" irányába
// Ezen értékkel lehet finomhangolni a kéz függőleges pozícióját a képernyőn.
// Növeld a negatív értéket, ha lejjebb akarod vinni.
glm_vec3_scale(camera.up, -0.4f, temp_vec); // Enyhén lefelé
glm_vec3_add(handPos, temp_vec, handPos);

// Offset a kamera "előre" irányába
// Ezen értékkel lehet finomhangolni a kéz távolságát a kamerától.
// Növeld az értéket, ha távolabb, csökkentsd, ha közelebb akarod.
glm_vec3_scale(camera.front, 0.7f, temp_vec); // Enyhén előre
glm_vec3_add(handPos, temp_vec, handPos);
// Alkalmazzuk az alapjárati (idle) lebegést a Y pozícióra
handPos[1] += sin(handAnimationTime) * handMaxIdleOffset;

// Alkalmazzuk a felvételi animáció eltolását előre/hátra
float pickupOffset = 0.0f;
if (isPickingUp) {
// A sin függvény 0-ról PI-ig tartó része egy ívet ír le (fel-le vagy előre-hátra mozgás)
pickupOffset = sin(handPickupProgress * GLM_PI) * pickupMaxForwardOffset;
}
// A kéz előre-hátra mozgatása a kamera előre vektorával
glm_vec3_scale(camera.front, pickupOffset, temp_vec);
glm_vec3_add(handPos, temp_vec, handPos);


glm_translate(model, handPos);
// Növeljük a kéz méretét, hogy jobban látható legyen.
// Az új modellhez valószínűleg kisebb skálázás is elég, de ez még finomhangolható.
glm_scale(model, (vec3){0.5f, 0.5f, 0.5f}); // Skálázás (finomhangolható)
// A kéz forgatása a kamera dőlésével (pitch)
// Enyhén forgatjuk a kéz tengelye körül, hogy "tartsa" az FPS nézetet.
glm_rotate(model, glm_rad(-camera.pitch), (vec3){1.0f, 0.0f, 0.0f});
// A kéz forgatása a kamera elfordulásával (yaw)
// A -90.0f eltolás a modell orientációjától függően lehet szükséges.
glm_rotate(model, glm_rad(-camera.yaw - 90.0f), (vec3){0.0f, 1.0f, 0.0f});
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, handModel.textureID);
drawModel(&handModel);

// Draw Cubes
for (int i = 0; i < NUM_CUBES; ++i) {
if (cubeActive[i]) {
glm_mat4_identity(model);
glm_translate(model, cubePositions[i]);
glm_scale(model, (vec3){0.5f, 0.5f, 0.5f}); // Scale down cubes
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, cubeModel.textureID);
drawModel(&cubeModel);
}
}

// Render Help Screen if active
if (showHelp) {
renderHelpScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
}

SDL_GL_SwapWindow(window);
}

freeModel(&grassModel);
freeModel(&cubeModel);
freeModel(&handModel);
freeModel(&characterModel);
freeModel(&mountainModel);

glDeleteProgram(shaderProgram);

SDL_GL_DeleteContext(glContext);
SDL_DestroyWindow(window);
SDL_Quit();

return 0;
}