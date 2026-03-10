Shader "Custom/01Lunares"
{
    Properties
    {
        [IntRange] _Dist("Distancia entre circulos", Range(0, 100)) = 20
        [IntRange] _Radio("Radio", Range(0, 50)) = 6
	    [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
    }

    SubShader
    {
        Tags 
        { 
            "RenderType" = "Opaque" 
            "Queue" = "Geometry-1"
            "RenderPipeline" = "UniversalPipeline" 
        }

        Pass
        {
            HLSLPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/DeclareOpaqueTexture.hlsl"

            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;

                float4 pos : TEXCOORD1;
            };

            TEXTURE2D(_BaseMap);
            SAMPLER(sampler_BaseMap);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _BaseMap_ST;
				int _Radio;
				int _Dist;
            CBUFFER_END

            Varyings vert(Attributes IN)
            {
                Varyings OUT;
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);
                // OUT.uv = TRANSFORM_TEX(IN.uv, _Base);
                //OUT.uv = TRANSFORM_TEX(IN.uv, _Base);

                OUT.pos = ComputeScreenPos(TransformObjectToHClip(IN.positionOS.xyz));

                return OUT;
            }

            half4 frag(Varyings IN) : SV_Target
            {
                float2 screenUV = IN.pos / IN.pos.w;
                float2 screenXY = screenUV * _ScreenParams.xy;

                // ecuacion del circulo 
                // (x-a)2 + (y-b)2 = r2
                // C = (a,b)
	            int x = (_ScreenParams.x / _Dist) + _Radio;
	            int y = (_ScreenParams.y / _Dist) + _Radio;

                int2 c = (x,y);
                int2 pos = (screenXY.x, screenXY.y);

                // dist si la distancia es menor que el radio lo pintas si no no

                if(distance(c, pos) <= _Radio)
                {
                    _BaseColor = _BaseColor * float4(0.5f, 0.5f, 0.5f, 0.5f);
                }

                return _BaseColor;
            }
            ENDHLSL
        }
    }
}
