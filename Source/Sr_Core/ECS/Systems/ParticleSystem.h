#pragma once

#include "Engine/Engine.h"
#include "Resource/Resource.h"

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "ECS/Components/Particle.h"
#include "ECS/Components/Transform.h"

using namespace SrEngine;

class ParticleSystem : public ECS::BaseSystem
{

public:
	ParticleSystem()
	{

		AddComponentSignature<Particle>();
		AddComponentSignature<Transform>();

		nr_particles = 500;
		for (GLuint i = 0; i < nr_particles; ++i)
		{
			particles.push_back(Particle());
		}
		shaders[0] = Shader(Resource.Program("PARTICLE"));

		particle_quad[] = {
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		// Fill mesh buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
		// Set mesh attributes
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindVertexArray(0);


	}

	void Update()
	{
		for (auto entity : entities)
		{
			auto& particle = ECS::Manager.GetComponent<Particle>(entity);
			auto& transform = ECS::Manager.GetCompList<Transform>(entity);
			
			GLuint nr_new_particles = 2;
			// Add new particles
			for (GLuint i = 0; i < nr_new_particles; ++i)
			{
				int unusedParticle = FirstUnusedParticle();
				RespawnParticle(particles[unusedParticle], particle, offset);
			}
			// Update all particles
			for (GLuint i = 0; i < nr_particles; ++i)
			{
				Particle& p = particles[i];
				p.Life -= Timer.deltaTime; // reduce life
				if (p.Life > 0.0f)
				{   // particle is alive, thus update
					p.Position -= p.Velocity * Timer.deltaTime;
					p.Color.a -= Timer.deltaTime * 2.5;
				}
			}
		}

	}

	void Render() override
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		shaders[0].Bind();
		for (Particle particle : particles)
		{
			if (particle.Life > 0.0f)
			{
				shaders[0].SetV4f("offset", particle.Position);
				shaders[0].SetV4f("color", particle.Color);
// 				Resource.Tex2D("particle");
// 				particleTexture.Bind();
// 				glBindVertexArray(particleVAO);
// 				glDrawArrays(GL_TRIANGLES, 0, 6);
// 				glBindVertexArray(0);
			}
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	GLuint lastUsedParticle = 0;
	GLuint FirstUnusedParticle()
	{
		// Search from last used particle, this will usually return almost instantly
		for (GLuint i = lastUsedParticle; i < nr_particles; ++i)
		{
			if (particles[i].Life <= 0.0f)
			{
				lastUsedParticle = i;
				return i;
			}
		}
		// Otherwise, do a linear search
		for (GLuint i = 0; i < lastUsedParticle; ++i)
		{
			if (particles[i].Life <= 0.0f)
			{
				lastUsedParticle = i;
				return i;
			}
		}
		// Override first particle if all others are alive
		lastUsedParticle = 0;
		return 0;
	}
	void RespawnParticle(Particle& particle, Particle& particleObj, glm::vec2 offset)
	{
		GLfloat random = ((rand() % 100) - 50) / 10.0f;
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
		particle.Position = particleObj.Position + random + offset;
		particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
		particle.Life = 1.0f;
		particle.Velocity = particleObj.Velocity * 0.1f;
	}


private:
	GLuint nr_particles;
	std::vector<Particle> particles;
	Shader shaders[1];
	GLuint VBO, VAO;
	GLfloat particle_quad[];
};
