# BossFightDemo

Pre-Intial Additions

SNonExplodingProjectile.cpp/h - For Projectile that does not explode and deals overlap damage a set number of times per actor

SAIBoss.cpp/h - Boss AI Character base class

EnemyFengMao_BP - Boss BP Derived from SAIBoss class

BossFeng_BT - FengMaoBoss Behavior Tree
BTDecorator_RandomChance - For determining the likelyhood that a particular Attack Sequence will execute

BossFeng Abilities

-Action_DashAttack 
      -Parent Class - SAction_ProjectileAttack
      -Projectile Class - Proj_DashAttack
      -Attack Anim Delay - .17
      -Attack Anim - Dash_Attack_Montage
      -Casting Sound - FengMao_Effort_Ability_Primary_Swing
      
-Action_FengGroundSmash
      -Parent Class - SAction_ProjectileAttack
      -Projectile Class - Proj_FengGroundSmash_Bleed
      -Attack Anim Delay - 1.0
      -Attack Anim - Ult_Mont(Ultimate Montage)
      
 -Action_FengGroundSmashAlt
      -Parent Class - SAction_ProjectileAttack
      -Projectile Class - Proj_FengGroundSmash_Stun
      -Attack Anim Delay - 1.0
      -Attack Anim - Ult_Mont(Ultimate Montage)
      -Casting Sound - FengMao_Effort_Ability_Ultimate
      
-Action_SpawnClones
      -Parent Class - SAction_ProjectileAttack
      -Projectile Class - None
      -Attack Anim Delay - 0.2
      -Attack Anim - SpawnMinions_Mont
      -Casting Sound - FengMao_Intro_Question
      
GreenCloneFengMao_BP - Clone Character Derived from SAICharacter
      -Mesh Material - M_GreenHologram_Inst
      -Spawn VFX - NS_NatureAEO
      -On Health Changed(AttributeComp) less than 0.0 spawn P_Destruction_ElectricGreen Particle effect
      
Clone Ability

Action_CloneDashAttack
      -Parent Class - SAction_ProjectileAttack
      -Projectile Class - Proj_CloneDashAttack
            -Impact VFX - P_FengMao_Melee_SuccessfulImpact
            -Impact Sound - Buff_Attack_7_2_Cue
      -Attack Anim Delay - .18
      -Attack Anim - Dash_Attack_Montage
      -Casting Sound - Buff_Attack_9_2_Cue
