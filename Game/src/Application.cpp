// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "Application.h"
#include <string>

Application::Application()
{
	m_config.readINIFile(ENGINEASSETS"game.ini");
	std::string assetPath(ENGINEASSETS);

	m_input = mkShare<GE::Input::InputManager>();

	m_scrennSize.x = RES_LOW_X;
	m_scrennSize.y = RES_LOW_Y;
	onResize((int)m_scrennSize.x, (int)m_scrennSize.y);
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);
	windowRename(std::string(m_config.data.windowTitle).c_str());

	// ------------------- BULLET SETUP  ------------------- //

	// collision configuration contains default setup for memory, collision setup
	collisionConfiguration = new btDefaultCollisionConfiguration();

	// the default collision dispatcher
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	// a general purpose broadphase
	overlappingPairCache = new btDbvtBroadphase();

	// the default constraint solver
	solver = new btSequentialImpulseConstraintSolver;

	// provide a high level interface that manages the physics objects and implements the update of all objects each frame
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, 0, 0));
	dynamicsWorld->setDebugDrawer(&m_debugDraw);


	// ------------------- BULLET SET    ------------------- //

	m_texture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[0]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_paddleTexture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[1]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_sphereObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[0]).c_str());
	m_paddleObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[1]).c_str());
	m_wallObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[2]).c_str());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	m_camera = mkShare<GE::Camera>(glm::vec3(0, 5, 0), glm::vec3(0, 0, -30.0f), m_scrennSize, 45.0f, 0.1f, 100.0f);
	m_debugDraw.setDebugCamera(m_camera);

	GE::Shader vertexShader(std::string(assetPath + m_config.data.shaderPaths[0]).c_str(), kVertexShader);
	GE::Shader pixelShader(std::string(assetPath + m_config.data.shaderPaths[1]).c_str(), kPixelShader);
	m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

	GE::Shader vertexShader2(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
	GE::Shader pixelShader2(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
	m_shaderProgramCollision = mkShare<GE::Program>(vertexShader2, pixelShader2);

	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player1Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player2Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("ball"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("wallBottom"), mkShare<GE::GameObject>()));

	shared<GE::Transform> transform;
	shared<GE::MeshRenderer> meshRenderer;
	shared<GE::BoxCollider> boxCollider;
	shared<GE::SphereCollider> sphereCollider;
	shared<GE::CollisionShape> collisionShape;
	shared<GE::RidigBody> rigidBody;

	// player1Paddle
	transform = m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player1Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player1Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("player1Paddle")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player1Paddle")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_paddleObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	m_gameObjects.at("player1Paddle")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player1Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	glm::vec3 aabbSize(boxCollider->m_boundingBox.extents);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("player1Paddle")->addComponent<GE::RidigBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 1.0f);

	// player2Paddle
	transform = m_gameObjects.at("player2Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, 0.0f, -60.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player2Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player2Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("player2Paddle")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player2Paddle")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_paddleObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("player2Paddle")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player2Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("player2Paddle")->addComponent<GE::RidigBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player2Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);

	// ball
	transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(0.0f, 0.0f, -30.0f));
	m_gameObjects.at("ball")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("ball")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("ball")->addComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider = m_gameObjects.at("ball")->getComponentShared<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_sphereObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);
	m_gameObjects.at("ball")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("ball")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btSphereShape(btScalar(transform->getScale().x)));
	m_gameObjects.at("ball")->addComponent<GE::RidigBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 1.0f);

	//  wall bottom
	transform = m_gameObjects.at("wallBottom")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(10.0f, 10.0f, 10.0f));
	transform->setPosition(glm::vec3(0.0f, -5.0f, -20.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("wallBottom")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("wallBottom")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	//boxCollider = m_gameObjects.at("wallBottom")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	//boxCollider->boundToObject(m_wallObject);
	//boxCollider->recomputeBounds(transform->getPosition());
	//boxCollider->setScreenRes(m_scrennSize);
	//aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	//m_gameObjects.at("wallBottom")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	//collisionShape = m_gameObjects.at("wallBottom")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	//collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	//m_gameObjects.at("wallBottom")->addComponent<GE::RidigBody>(GE::kRigidBody);
	//rigidBody = m_gameObjects.at("wallBottom")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
	//rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);


	// ------------------- BULLET GAMEOBJECTS CONFIG ------------------- //
	// paddles
	{
		// set up the ball and add rigidBody to dynamics world
		shared<GE::RidigBody> rBody = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
		dynamicsWorld->addRigidBody(m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody().get());
		rBody = m_gameObjects.at("player2Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody);
		dynamicsWorld->addRigidBody(rBody->getRigidBody().get());
	}

	// walls
	{
		// set up the ball and add rigidBody to dynamics world
		//dynamicsWorld->addRigidBody(m_gameObjects.at("wallBottom")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody().get());
	}

	// ball
	{
		// set up the ball and add rigidBody to dynamics world
		m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(btVector3(0, 0, 5));
		dynamicsWorld->addRigidBody(m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody().get());
	}

	// ------------------- BULLET GAMEOBJECTS CONFIGED ------------------- //


	m_screenMouse = mkShare<GE::Input::MouseConverter>(m_camera->getProjection(), m_camera->getView(), m_scrennSize);

	// which level to start on
	m_activeLevel = 0;
}

Application::~Application()
{
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;
	collisionShapes.clear();
	m_gameObjects.clear();
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{
	static float refreshDT = 0.0f;
	btTransform updateTransform;
	std::string collisionKeyA;
	std::string collisionKeyB;
	refreshDT += dt;

	// update input
	m_input->update();

	// cap how often you can change selection - make input update more accurate
	if (refreshDT >= 0.05f)
	{
		refreshDT = 0.0f;
	}


	//------------------ input update start ------------------ //

	// apply velocity to the the paddle
	shared<btRigidBody> paddle1 = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody();
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() == 0.0f)
			paddle1->setLinearVelocity(btVector3(0, 1, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() == 0.0f)
			paddle1->setLinearVelocity(btVector3(0, -1, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() != 0.0f)
			paddle1->setLinearVelocity(btVector3(0, 0, 0));
	}

	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getX() == 0.0f)
			paddle1->setLinearVelocity(btVector3(-1, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getX() == 0.0f)
			paddle1->setLinearVelocity(btVector3(1, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getX() != 0.0f)
			paddle1->setLinearVelocity(btVector3(0, 0, 0));
	}

	//------------------ input update end ------------------ //



	//------------------ stepsimulation start ------------------ //
	{
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);


		// handle overlapping objects, if there are any
		for (int i = 0; i < overlappingObjectsPairsCount(); i++)
		{
			// get a pair of overlapping objects
			btVector3  collisionNormal = getOverlappingGameObjects(collisionKeyA, collisionKeyB, i);
			GE::consoleLog("collisionNormal ", collisionNormal);
			// if both keys are no empty, perform collision response logic
			if (!collisionKeyA.empty() && !collisionKeyB.empty())
			{
				//std::cout << collisionKeyA.c_str() << " " << collisionKeyB.c_str() << std::endl;
			
				// if player1Paddle and ball collider
				{
					// reflect the ball in the opposite direction
					if (collisionKeyA == "ball" || collisionKeyB == "ball" && collisionKeyA == "player1Paddle" || collisionKeyB == "player1Paddle")
					{
						//shared<btRigidBody >ballBody = m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody();
						//ballBody->setAngularVelocity(btVector3(0, 2.5f, 0));
						//btQuaternion quat = ballBody->getOrientation();
						//GE::consoleLog("quat ", quat.getAxis());
						if (collisionNormal != btVector3(0, 0, 0))
						{
							m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(-(collisionNormal * 5.0f));
							m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->setAngularVelocity(btVector3(0, 0, 0));
						}

					}
				}
			
				// if player2Paddle and ball collider
				{
					// reflect the ball in the opposite direction
					if (collisionKeyA == "ball" || collisionKeyB == "ball" && collisionKeyA == "player2Paddle" || collisionKeyB == "player2Paddle")
					{
						if (collisionNormal != btVector3(0, 0, 0))
						{
							m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(-(collisionNormal * 5.0f));
							m_gameObjects.at("player2Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->setAngularVelocity(btVector3(0, 0, 0));
						}
					}
				}
			}
		}
		//------------------ stepsimulation end ------------------ //
	}

	// update Transform Component with changes from Bullet Engine
	glm::vec3 glmOrigin;
	{
		btTransform bttransform = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getRigidBody()->getWorldTransform();
		glmOrigin = glm::vec3(bttransform.getOrigin().getX(), bttransform.getOrigin().getY(), bttransform.getOrigin().getZ());
		GE::consoleLog("glmOrigin ", glmOrigin);
		m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform)->setPosition(glmOrigin);
	}


	m_gameObjects.at("ball")->getComponentShared<GE::RidigBody>(GE::kRigidBody)->getBodyWorldTransform(updateTransform);


	// update Transform Component with changes from Bullet Engine
	btVector3 origin = updateTransform.getOrigin();
	btVector3 rotation = updateTransform.getRotation().getAxis();
	glmOrigin = glm::vec3(origin.getX(), origin.getY(), origin.getZ());

	glm::vec3 glmRotation = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->getRotation();
	glmRotation.x += rotation.getX();
	glmRotation.y += rotation.getY();
	glmRotation.z += rotation.getZ();
	m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->setPosition(glmOrigin);
	m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->setRotation(glmRotation);



	// update
	m_gameObjects.at("ball")->setInput(m_input);
	m_gameObjects.at("ball")->update(dt);
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->second->isActive())
			it->second->draw();
	}

	dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb);
	dynamicsWorld->debugDrawWorld();

	glutSwapBuffers();
}

btVector3 Application::getOverlappingGameObjects(std::string& keyA, std::string& keyB, int pairNumber)
{
	// get the two objects that have collided
	btPersistentManifold* manifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(pairNumber);
	const btCollisionObject* const objectA = manifold->getBody0();
	const btCollisionObject* const objectB = manifold->getBody1();
	btVector3 normalAtCollision(0, 0, 0);
	int contacts = manifold->getNumContacts();

	// for each contact point between the objects
	for (int j = 0; j < contacts; j++) 
	{
		btManifoldPoint& pt = manifold->getContactPoint(j);
		normalAtCollision = pt.m_normalWorldOnB;
	}

	// find which GameObject these two objects are
	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		// gameObject is active else breaks once both keys are found
		if (it->second->isActive() && keyA.empty() || keyB.empty())
		{
			shared<GE::RidigBody> rbBody = it->second->getComponentShared<GE::RidigBody>(GE::kRigidBody);
			btTransform bttransform = rbBody->getRigidBody()->getWorldTransform();
			btVector3 oA = objectA->getWorldTransform().getOrigin();
			btVector3 oB = objectB->getWorldTransform().getOrigin();

			// which key matches this transform
			if (oA == bttransform.getOrigin())
				keyA = it->first;

			if (oB == bttransform.getOrigin())
				keyB = it->first;
		}
		else
			break;
	}

	return normalAtCollision;
}

