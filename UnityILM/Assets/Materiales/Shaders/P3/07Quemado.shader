Shader "Custom/07Quemado"
{
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
        [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
        [MainTexture] _MainTex ("Base (RGB)", 2D) = "" {}
    	
    	_CutThresold("Cutoff thresold", float) = 0
    	_CutHeight("Cutoff height", Range(0.0, 1.0)) = 0.3
    	_CutWidth("Cut width", Range(0.0, 1)) = 0.1
    	_NoiseScale("Nosie Scale", float) = 20
    }

    SubShader
    {
        Tags { "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }

        Pass
        {
            HLSLPROGRAM

            float2 unity_gradientNoise_dir(float2 p)
            {
                p = p % 289;
                float x = (34 * p.x + 1) * p.x % 289 + p.y;
                x = (34 * x + 1) * x % 289;
                x = frac(x / 41) * 2 - 1;
                return normalize(float2(x - floor(x + 0.5), abs(x) - 0.5));
            }
            
            float unity_gradientNoise(float2 p)
            {
                float2 ip = floor(p);
                float2 fp = frac(p);
                float d00 = dot(unity_gradientNoise_dir(ip), p);
                float d01 = dot(unity_gradientNoise_dir(ip + float2(0, 1)), fp - float2(0, 1));
                float d10 = dot(unity_gradientNoise_dir(ip + float2(1, 0)), fp - float2(1, 0));
                float d11 = dot(unity_gradientNoise_dir(ip + float2(1, 1)), fp - float2(1, 1));
                fp = fp * fp * fp * (fp * (fp * 6 - 15) + 10);
                return lerp(lerp(d00, d01, fp.y), lerp(d10, d11, fp.y), fp.x);
            }

            void Unity_GradientNoise_float(float2 UV, float Scale, out float Out)
            {
               Out = unity_gradientNoise(UV * Scale) + 0.5; 
            }

            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"

            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;
                float4 positionLocal : POSITION1;
            };

            TEXTURE2D(_BaseMap);
            SAMPLER(sampler_BaseMap);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _BaseMap_ST;
				float _CutThresold;
				float _CutHeight;
				float _CutWidth;
				float _NoiseScale;

                float4 _MainTex_ST;
            CBUFFER_END

            Varyings vert(Attributes IN)
            {
                Varyings OUT;
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);
                OUT.positionLocal = IN.positionOS;
                OUT.uv = TRANSFORM_TEX(IN.uv, _BaseMap);
                return OUT;
            }

            half4 frag(Varyings IN) : SV_Target
            {   
                float ruido;
                Unity_GradientNoise_float(IN.uv, _NoiseScale, ruido);

                float slope = 1.0 * (1 - -1) / (1 - 0);
				ruido = 0 + slope * (ruido - 0);
            	float4 color = float4(1,1,1,1);
                float4 coor = float4(IN.positionLocal.x + ruido * _CutHeight, IN.positionLocal.y + ruido * _CutHeight, IN.positionLocal.z, IN.positionLocal.w);



            	if (coor.y > _CutThresold - _CutHeight 
                    && coor.y < _CutThresold + _CutHeight
                    && coor.x > _CutThresold - _CutWidth && coor.x < _CutThresold + _CutWidth) 
                {
                    discard;
                }
                else 
                {
                    float4 colorTex = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, IN.uv) * _BaseColor;

                    if (coor.x <= _CutWidth)
                    {
	                    float xL = lerp(colorTex.x, 1, _CutWidth);
	                    float yL = lerp(colorTex.y, 1, _CutWidth);
	                    float zL = lerp(colorTex.z, 0, _CutWidth);
	                    
	                    color = float4(xL, yL, zL, 1);
                    }
                	else
                    {
	                    color = colorTex;
                    }
                }

                return color;
            }
            ENDHLSL
        }
    }
}
