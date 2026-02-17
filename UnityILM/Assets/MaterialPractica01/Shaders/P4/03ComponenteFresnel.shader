Shader "Custom/03ComponenteFresnel"
{
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
    	[SpecularColor] _SpecularColor("Specular color", Color) = (1,0,0,1) // color de la luz especular
    	[GlossPower] _GlossPower("Gloss Power", float) = 100 // 
    	[FresnelPower] _FresnelPower("Fresnel Power", float) = 10 // 
    	
        [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
    }

    SubShader
    {
        Tags { "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }

        Pass
        {
            HLSLPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Lighting.hlsl"

            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0;

                float3 normal : NORMAL;
            };

            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;

                float4 specularLighting : TEXCOORD1;
                float4 diffuseLighting : COLOR;

                float3 normalWS : TEXCOORD2;
                float3 view : TEXCOORD3;
            };

            TEXTURE2D(_BaseMap);
            SAMPLER(sampler_BaseMap);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                half4 _SpecularColor;
                float4 _BaseMap_ST;
                float _GlossPower;
                float _FresnelPower;
            CBUFFER_END

            // vs
            Varyings vert(Attributes IN)
            {
                Varyings OUT;

                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);

                OUT.normalWS = TransformObjectToWorldNormal(IN.normal);

                float4 positionWS = mul(unity_ObjectToWorld, IN.positionOS);
                OUT.view = GetWorldSpaceNormalizeViewDir(positionWS.xyz);
                OUT.uv = IN.uv;
                return OUT;
            }

            // ps
            half4 frag(Varyings IN) : SV_Target
            {
                IN.normalWS = normalize(IN.normalWS);
                IN.view = normalize(IN.view); 

                // -- ambiente
                float3 ambient = half3(unity_SHAr.w, unity_SHAg.w, unity_SHAb.w);

                Light mainLight = GetMainLight();
                float mainLightIntensity = max(0, dot(IN.normalWS, mainLight.direction));

                // -- difusa
                float3 diffuse = mainLight.color * mainLightIntensity;
                float4 diffuseLighting = float4(ambient + diffuse, 1);

                // -- especular
                float3 halfVetor = normalize(mainLight.direction + IN.view);
                float specular = max(0, dot(IN.normalWS, halfVetor));
                specular = pow(specular, _GlossPower);
                float3 specularColor = mainLight.color * specular;
                float4 specularLighting = float4(specularColor, 1.0);

                // -- fresnel
                float3 fresnelColor = mainLight.color * pow(1- max(0, dot((IN.normalWS), IN.view)), _FresnelPower);
                float4 fresnelLighting = float4(fresnelColor, 1.0);

                return _BaseColor * diffuseLighting + specularLighting + fresnelLighting;
            }
            ENDHLSL
        }
    }
}
