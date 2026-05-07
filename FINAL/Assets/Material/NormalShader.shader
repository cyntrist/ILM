Shader "Custom/NormalShader"
{
    Properties
    {
        [MainTexture] _NormalTex("Base Map", 2D) = "white" {}
    }

    SubShader
    {
        Tags { "LightMode" = "ForwardBase" "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }

        Pass
        {
            HLSLPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"

            // VS
            struct Attributes
            {
                float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 tangent : TANGENT;
				float2 uv : TEXCOORD0;
            };

            // PS
            struct Varyings
            {
                float4 vertex : SV_POSITION;
				float2 uv : TEXCOORD0;
				float3 tbn[3] : TEXCOORD1; // TEXCOORD2; TEXCOORD3;
            };

            TEXTURE2D(_BaseMap);
            SAMPLER(_NormalTex);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _BaseMap_ST;
            CBUFFER_END

            // VS
            Varyings vert(Attributes IN)
            {
                Varyings OUT;

                OUT.pos = OUT.pos2 = TransformObjectToHClip(IN.positionOS.xyz);

                // segunda version
                OUT.pos3 = ComputeScreenPos(TransformObjectToHClip(IN.positionOS.xyz));

                return OUT;
            }

            // PS
            half4 frag(Varyings IN) : SV_Target
            {
                // primera version
            	//return ComputeScreenPos(float4(IN.pos2.xy / IN.pos2.w, 0.0f, 1.0f));

                // segunda version
                return float4(abs(IN.pos3.xy / IN.pos3.w), 0.0f, 1.0f);

            }
            ENDHLSL
        }
    }
}

